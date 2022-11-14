#pragma once
#include "Request.h"
#include "OrderType.h"

#include <list>

class Order
{
public:
	explicit Order(const std::string& treader, const OrderType& type, int quantity, int price);
	
	Order(const Order&) = default;
	Order(Order&&) = default;
	Order& operator=(const Order&) = default;
	Order& operator=(Order&&) = default;

	friend std::ostream& operator<<(std::ostream& os, const Order& order);

	const std::string& traderIdentifier() const;
	int quantity() const;
	int price() const;
	const OrderType& type() const;
	void setQuantity(int quantity);

private:
	std::string _traderIdentifier;
	const OrderType& _type;
	int _quantity = 0;
	int _price = 0;

};

typedef std::list<Order> Orders;

namespace OrderUtils
{
	class OrderComparator
	{
	public:
		bool operator()(const Order& a, const Order& b) const;
	};

	void Normalize(Orders& orders);
}
