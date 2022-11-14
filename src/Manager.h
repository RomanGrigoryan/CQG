#pragma once
#include "Request.h"
#include "Order.h"
#include "SequentialPriorityQueue.h"

#include <list>
#include <functional>

class Manager
{
public:
	Manager();
	Orders processRequest(Request::Ptr request);
private:
	typedef std::function<bool(const Request::Ptr&, const Request::Ptr&)> RequestCompareType;
	typedef SequentialPriorityQueue<Request::Ptr, RequestCompareType> RequestQueue;
	
	Orders processBuyRequest(Request::Ptr request);
	Orders processSellRequest(Request::Ptr request);
	Orders process(RequestQueue& queue, Request::Ptr request, RequestCompareType compare);

private:
	static RequestCompareType salersCompare;
	static RequestCompareType buyersCompare;

	SequentialPriorityQueue<Request::Ptr, RequestCompareType> _restingSalers;
	SequentialPriorityQueue<Request::Ptr, RequestCompareType> _restingBuyers;
};
