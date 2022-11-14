#pragma once
#include "Request.h"

#include <queue>
#include <vector>
#include <utility>
#include <functional>

template<class T, class Compare>
class SequentialPriorityQueue
{
	typedef std::pair<T, int> ValueType;

	class SequentialComparator
	{
	public:
		explicit SequentialComparator(Compare c) 
			: _compare(c)
	       	{}

		bool operator()(const ValueType& a, const ValueType& b)
		{
			if (_compare(a.first, b.first) != _compare(b.first, a.first)) {
				return _compare(a.first, b.first);
			}
			return a.second > b.second;
		}
	
	private:
		Compare _compare;
	};

public:
	explicit SequentialPriorityQueue(Compare c) 
		: _priorityQueue(SequentialComparator(c))
	{}
	
	bool empty() const
	{
		return _priorityQueue.empty();
	}

	const T& top() const
	{
		return _priorityQueue.top().first;
	}

	void pop()
	{
		_priorityQueue.pop();
	}

	void push(const T& value)
	{
		_priorityQueue.push(std::make_pair(value, _sequence++));
	}
	
	void push(T&& value) 
	{
		_priorityQueue.push(std::move(std::make_pair(value, _sequence++)));
	}

private:
	size_t _sequence = 0;
	std::priority_queue<ValueType, std::vector<ValueType>, SequentialComparator> _priorityQueue;

};
