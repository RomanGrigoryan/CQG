// CQG_TradeMatchingEngine_Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "catch.hpp"

#include "../src/Request.h"
#include "../src/RequestParser.h"
#include "../src/OrderType.h"


#include <algorithm>

#include "TestUtils.h"

TEST_CASE("RequestParser", "[RequestParser]") 
{   
        RequestParser parser;
        Request::Ptr result = nullptr;
        SECTION("Input: empty string", "[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string()), RequestParserExeption);
           
        }
        
        SECTION("Input: T","[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string("T")), RequestParserExeption);
           
        }
        
        SECTION("Input: T1 e 1 50", "[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string("T1 e 1 50")), RequestParserExeption);
           
        }
        
        SECTION("Input: T1 S a 50", "[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string("T1 S a 50")), RequestParserExeption);
           
        }
        
        SECTION("Input: T1 B 1 A", "[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string("T1 B 1 A")), RequestParserExeption);
           
        }
        
        SECTION("Input: T1 B 1 55555555555555555", "[RequestParser]")
        {
           REQUIRE_THROWS_AS(parser.parseRequest(std::string("T1 B 1 55555555555555555")), RequestParserExeption);
           
        }
        
        SECTION("Input: T1 B 1 50", "[RequestParser]")
        {
           REQUIRE_NOTHROW(result = parser.parseRequest(std::string("T1 B 1 50")));
           REQUIRE(result != nullptr);
           REQUIRE(result->traderIdentifier() == "T1");
           REQUIRE(OrderType::Type(result->requestType()) == OrderType::Type(OrderType::OrderBuy));
           REQUIRE(result->quantity() == 1);
           REQUIRE(result->price() == 50);         
         
        }
        
        SECTION("Input: T1 S 1 50","[RequestParser]")
        {
           
           REQUIRE_NOTHROW(result = parser.parseRequest(std::string("T1 S 1 50")));
           REQUIRE(result != nullptr);
           REQUIRE(result->traderIdentifier() == "T1");
           REQUIRE(OrderType::Type(result->requestType()) == OrderType::Type(OrderType::OrderSell));
           REQUIRE(result->quantity() == 1);
           REQUIRE(result->price() == 50);
        }
}

