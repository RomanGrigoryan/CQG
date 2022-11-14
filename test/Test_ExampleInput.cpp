// CQG_TradeMatchingEngine_Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "catch.hpp"

#include "../src/Manager.h"
#include "../src/Request.h"
#include "../src/Order.h"
#include "../src/OrderType.h"

#include "TestUtils.h"

TEST_CASE("Manager", "[Manager]") 
{
    Manager manager;
    {
        auto result = manager.processRequest(Request::createRequest("T1", OrderType::OrderBuy, 5, 30));
        REQUIRE(result.empty());
    }
    {
    	auto result = manager.processRequest(Request::createRequest("T2", OrderType::OrderSell, 5, 70));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T3", OrderType::OrderBuy, 1, 40));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T4", OrderType::OrderSell, 2, 60));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T5", OrderType::OrderSell, 3, 70));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T6", OrderType::OrderSell, 20, 80));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T7", OrderType::OrderSell, 1, 50));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T2", OrderType::OrderSell, 5, 70));
        REQUIRE(result.empty());
    }
    {
        auto result = manager.processRequest(Request::createRequest("T1", OrderType::OrderBuy, 1, 50));
        REQUIRE(!result.empty());
        Orders expResult = { Order("T7", OrderType::OrderSell, 1, 50), Order("T1", OrderType::OrderBuy, 1, 50) };
        auto iterf = result.begin(); 
        auto iters = expResult.begin();
        REQUIRE(result.size() == expResult.size());
        for(; iterf != result.end() && iters != expResult.end() ; iterf++, iters++){
            REQUIRE(TestUtils::orderComparator(*iterf, *iters));
        }
         
    }
    {
        auto result = manager.processRequest(Request::createRequest("T1", OrderType::OrderBuy, 3, 60));
        REQUIRE(!result.empty());
        Orders expResult = { Order("T4", OrderType::OrderSell, 2, 60), Order("T1", OrderType::OrderBuy, 2, 60) };
        auto iterf = result.begin(); 
        auto iters = expResult.begin();
        REQUIRE(result.size() == expResult.size());
        for(; iterf != result.end() && iters != expResult.end() ; iterf++, iters++){
            REQUIRE(TestUtils::orderComparator(*iterf, *iters));
        }
    }
    {
        auto result = manager.processRequest(Request::createRequest("T7", OrderType::OrderSell, 2, 50));
        REQUIRE(!result.empty());
        Orders expResult = {  Order("T1", OrderType::OrderBuy, 1, 60), Order("T7", OrderType::OrderSell, 1, 60) };
        auto iterf = result.begin(); 
        auto iters = expResult.begin();
        REQUIRE(result.size() == expResult.size());
        for(; iterf != result.end() && iters != expResult.end() ; iterf++, iters++){
            REQUIRE(TestUtils::orderComparator(*iterf, *iters));
        }
    }
    {
        auto result = manager.processRequest(Request::createRequest("T8", OrderType::OrderBuy, 10, 90));
        REQUIRE(!result.empty());
        Orders expResult = { Order("T2", OrderType::OrderSell, 1, 70)
                           , Order("T5", OrderType::OrderSell, 3, 70) 
                           , Order("T2", OrderType::OrderSell, 5, 70) 
                           , Order("T7", OrderType::OrderSell, 1, 50) 
                           , Order("T8", OrderType::OrderBuy, 1, 50) 
                           , Order("T8", OrderType::OrderBuy, 5, 70) 
                           , Order("T8", OrderType::OrderBuy, 3, 70) 
                           , Order("T8", OrderType::OrderBuy, 1, 70) 
                           };
        auto iterf = result.begin(); 
        auto iters = expResult.begin();
        REQUIRE(result.size() == expResult.size());
        for(; iterf != result.end() && iters != expResult.end() ; iterf++, iters++){
            REQUIRE(TestUtils::orderComparator(*iterf, *iters));
        }
    }
}

