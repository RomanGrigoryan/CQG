#pragma once

#include <ostream>

class OrderType
{
public:
	enum class Type {
		Buy,
		Sell
	};

	static const OrderType OrderBuy;
	static const OrderType OrderSell;
	
	bool operator!=(const OrderType& o) const;  
	bool operator<(const OrderType& o) const;

	operator Type() const;
	operator char() const;

private:
	OrderType(char i, char o, Type t);

	char _inputChar;
	char _outputChar;
	Type _type;
};
