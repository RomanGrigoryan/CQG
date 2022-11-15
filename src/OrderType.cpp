#include "OrderType.h"

const OrderType OrderType::OrderBuy('B', '+', Type::Buy);
const OrderType OrderType::OrderSell('S', '-', Type::Sell);

OrderType::OrderType(char i, char o, Type t)
	: _inputChar(i)
	, _outputChar(o)
	, _type(t)
{}

bool OrderType::operator!=(const OrderType& o)const  
{
	return _type != o._type;
}

bool OrderType::operator<(const OrderType& o)const
{
	return _type < o._type;
}

OrderType::operator Type() const
{
	return _type;
}

OrderType::operator char() const
{
	return _outputChar;
}
