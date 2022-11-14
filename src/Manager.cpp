#include "Manager.h"

#include <cassert>
#include <set>
#include <tuple>
#include <list>
#include <functional>
#include <iostream>

Manager::RequestCompareType Manager::salersCompare = [](const Request::Ptr& a, const Request::Ptr& b) -> bool
{
	return a->price() > b->price();
};

Manager::RequestCompareType Manager::buyersCompare = [](const Request::Ptr& a, const Request::Ptr& b) -> bool
{
	return a->price() < b->price();
};

Manager::Manager()
	: _restingSalers(salersCompare)
	, _restingBuyers(buyersCompare)
{}

Orders Manager::processRequest(Request::Ptr request)
{
	assert(request);
	switch (OrderType::Type(request->requestType())) {
		case OrderType::Type::Buy: 
			return processBuyRequest(request);
		case OrderType::Type::Sell: 
			return processSellRequest(request);
		default:
			assert(0);
			return Orders();
	}
}

Orders Manager::processBuyRequest(Request::Ptr request)
{
	RequestCompareType compare = [](const Request::Ptr& a, const Request::Ptr& b) -> bool {
			return a->price() <= b->price();
		};
	Orders  result = std::move(process(_restingSalers, request, compare));

	if (request->quantity() != 0) {
		_restingBuyers.push(request);
	}

	return result;
}

Orders Manager::processSellRequest(Request::Ptr request)
{
	RequestCompareType compare = [](const Request::Ptr& a, const Request::Ptr& b) -> bool {
			return a->price() >= b->price();
		};
	Orders result = std::move(process(_restingBuyers, request, compare));
	if (request->quantity() != 0) {
		_restingSalers.push(request);
	}

	return result;
}

Orders Manager::process(RequestQueue& queue, Request::Ptr request, RequestCompareType compare)
{
	Orders result;
	while (!queue.empty() && request->quantity() != 0) {
		const auto& queuedRequest = queue.top();
		if (compare(queuedRequest, request)) {
			int quantity = std::min(request->quantity(), queuedRequest->quantity());
			result.push_front(Order(queuedRequest->traderIdentifier(), queuedRequest->requestType(), quantity, queuedRequest->price()));
			result.push_back(Order(request->traderIdentifier(), request->requestType(), quantity, queuedRequest->price()));
			request->setQuantity(request->quantity() - quantity);
			queuedRequest->setQuantity(queuedRequest->quantity() - quantity);

			if (queuedRequest->quantity() == 0) {
				queue.pop();
			}
		}
		else {
			break;
		}
	}
	return result;
}
