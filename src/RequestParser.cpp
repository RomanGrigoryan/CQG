#include "RequestParser.h"
#include "OrderType.h"

#include <sstream>
#include <algorithm>
#include <limits>
#include <cctype>

Request::Ptr RequestParser::parseRequest(const std::string& input) const
{
	try {
		Tokens tokens;
		tokenize(input, tokens);
		return Request::createRequest(tokens[0]
			, tokens[1] == "B" ? OrderType::OrderBuy : OrderType::OrderSell
			, std::stoi(tokens[2])
			, std::stoi(tokens[3])
		);
	}
	catch (const std::out_of_range&) {
		throw RequestParserExeption("<Quantity> and <Price> should be valid integers.");
	};
}

void RequestParser::tokenize(const std::string& input, RequestParser::Tokens& tokens) const
{
	std::stringstream ss(input);
	std::string token;
	while (std::getline(ss, token, ' ')) {
		tokens.push_back(token);
	}
	validate(tokens);
}

void RequestParser::validate(const RequestParser::Tokens& tokens) const
{
	if (tokens.size() != 4) {
		throw RequestParserExeption("Input should consist of 4 fields, separated by space.");
	}

	if (!std::all_of<decltype(tokens[0].begin()), int(int)>(tokens[0].begin(), tokens[0].end(), &std::isalnum)) {
		throw RequestParserExeption("<Trader Identifier> should be an alpha-numeric string.");
	}

	if (!(tokens[1] == "B" || tokens[1] == "S")) {
		throw RequestParserExeption("<Side> should be a single character: 'B' or 'S'.");
	}

	if (!std::all_of<decltype(tokens[2].begin()), int(int)>(tokens[2].begin(), tokens[2].end(), &std::isdigit)) {
		throw RequestParserExeption("<Quantity> should be an integer.");
	}

	if (!std::all_of<decltype(tokens[3].begin()), int(int)>(tokens[3].begin(), tokens[3].end(), &std::isdigit)) {
		throw RequestParserExeption("<Price> should be an integer.");
	}
}
