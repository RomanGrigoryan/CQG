#pragma once
#include "../src/Order.h"

#include <functional>

namespace TestUtils
{
   extern std::function<bool(const Order& r, const Order& er)> orderComparator;
}
