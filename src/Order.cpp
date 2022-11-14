#include "Order.h"

#include <algorithm>
#include <functional>
#include <iterator>

Order::Order(const std::string& traderIdentifier, const OrderType& type, int quantity, int price)
	: _traderIdentifier(traderIdentifier)
	, _type(type)
	, _quantity(quantity)
	, _price(price)
{}

const std::string& Order::traderIdentifier() const
{
	return _traderIdentifier;
}

const OrderType& Order::type() const
{
	return _type;
}

int Order::quantity() const
{
	return _quantity;
}

void Order::setQuantity(int quantity)
{
	_quantity = quantity;
}

int Order::price() const
{
	return _price;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
	os << order.traderIdentifier() << order.type() << order.quantity() << "@" << order.price();
	return os;
}

namespace OrderUtils
{
		bool OrderComparator::operator()(const Order& a, const Order& b) const
		{
			if (a.traderIdentifier() != b.traderIdentifier()) return a.traderIdentifier() < b.traderIdentifier();
			if (a.type() != b.type()) return a.type() < b.type();
			return a.price() < b.price();
		}
	
		template<typename Container, typename Comparator, typename Merger>
		class MergeInserter : public std::iterator<std::output_iterator_tag, void, void, void, void>
		{
		public:
			explicit MergeInserter(Container& cont, Comparator c, Merger m)
				: container(&cont)
				, _c(c)
				, _m(m)
			{}

			MergeInserter& operator=(const typename Container::value_type& value) {
				if (container->empty() || _c(container->back(), value)) {
					container->push_back(value);
				}
				else {
					_m(container->back(), value);
				}
				return *this;
			}
	
			MergeInserter& operator*() noexcept {
				return *this;
			}
	
			MergeInserter& operator++() noexcept {
				return *this;
			}
	
		private:
			Container* container;
			Comparator _c;
			Merger _m;
		};
	
	void Normalize(Orders& orders)
	{
		if (orders.empty()) {
			return;
		}
		OrderComparator c;
		orders.sort(c);
		Orders normalizedOrders;
		std::function<void(Order&, const Order&)> m = 
			[](Order& f, const Order& s) { 
			f.setQuantity(f.quantity() + s.quantity()); 
		
		};
		MergeInserter<Orders, OrderComparator, decltype(m)> mi(normalizedOrders, c, m);
		std::copy(orders.begin(), orders.end(), mi);
		orders = std::move(normalizedOrders);
	}
}
