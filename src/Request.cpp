#include "Request.h"

#include <ostream>

Request::Request(const std::string& identifier, const OrderType& type, int quantity, int price)
	: _traderIdentifier(identifier)
	, _type(type)
	, _quantity(quantity)
	, _price(price)
{}

Request::Ptr Request::createRequest(const std::string& identifier, const OrderType& type, int quantity, int price)
{
	return Ptr(new Request(identifier, type, quantity, price));
}

const std::string& Request::traderIdentifier() const
{
	return _traderIdentifier;
}

const OrderType& Request::requestType() const
{
	return _type;
}

int Request::quantity() const
{
	return _quantity;
}

void Request::setQuantity(int quantity)
{
	_quantity = quantity;
}

int Request::price() const
{
	return _price;
}