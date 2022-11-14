// CQG_TradeMatchingEngine_Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "catch.hpp"

#include "../src/Order.h"
#include "../src/OrderType.h"

#include <algorithm>

#include "TestUtils.h"

TEST_CASE("Orders", "[Orders]") 
{
    {
        Orders result = { Order("T2", OrderType::OrderSell, 1, 70)
                           , Order("T5", OrderType::OrderSell, 3, 70) 
                           , Order("T2", OrderType::OrderSell, 5, 70) 
                           , Order("T7", OrderType::OrderSell, 1, 50) 
                           , Order("T8", OrderType::OrderBuy, 1, 50) 
                           , Order("T8", OrderType::OrderBuy, 5, 70) 
                           , Order("T8", OrderType::OrderBuy, 3, 70) 
                           , Order("T8", OrderType::OrderBuy, 1, 70) 
                           };
        
        OrderUtils::Normalize(result);
        REQUIRE(!result.empty());
        Orders expResult = { Order("T2", OrderType::OrderSell, 6, 70)
                           , Order("T5", OrderType::OrderSell, 3, 70)
                           , Order("T7", OrderType::OrderSell, 1, 50) 
                           , Order("T8", OrderType::OrderBuy, 2, 50) 
                           , Order("T8", OrderType::OrderBuy, 9, 70)
                           };
        auto iterf = result.begin(); 
        auto iters = expResult.begin();
        REQUIRE(result.size() == expResult.size());
        for(; iterf != result.end() && iters != expResult.end() ; iterf++, iters++){
            REQUIRE(TestUtils::orderComparator(*iterf, *iters));
        }
    }
}

