#pragma once
#include "OrderType.h"

#include <string>
#include <memory>
#include <ostream>

class Request
{
public:
	typedef std::shared_ptr<Request> Ptr;
	static Request::Ptr createRequest(const std::string& identifier, const OrderType& type, int quantity, int price);

	const std::string& traderIdentifier() const;
	const OrderType& requestType() const;
	int quantity() const;
	void setQuantity(int quantity);
	int price() const;

private:
	Request(const std::string& identifier, const OrderType& type, int quantity, int price);
	
	Request(const Request&) = delete;
	Request(Request&&) = delete;
	Request& operator=(const Request&) = delete;
	Request operator=(Request&&) = delete;

private:
	std::string _traderIdentifier;
	const OrderType& _type;
	int _quantity;
	int _price;
};
