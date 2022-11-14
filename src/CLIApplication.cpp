#include "CLIApplication.h"

#include "RequestParser.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <cstring>

int CLIApplication::exec()
{
	help();
	while (true) {
		Command command = readCommand();
		switch (command.type) {
			case Command::Type::Input:
				input(command.params);
				break;
			case Command::Type::Help:
				help();
				break;
			case Command::Type::Exit:
				return 0;
		}
	}
}

CLIApplication::Command CLIApplication::readCommand() const
{
	const static std::map<std::string, Command::Type> commandMap = {
		{ "exit", Command::Type::Exit}, 
		{ "help", Command::Type::Help},
	};


	Command command;
	std::string line;
	std::getline(std::cin, line);

	auto iter = commandMap.find(line);
	if(iter != commandMap.end()) {
		command.type = iter->second;
	} else if(std::cin.eof()) {
		command.type = Command::Type::Exit;
	} else {
		command.params = std::move(line);
	}

	return command;
}

void CLIApplication::input(const std::string& params)
{
	try {
		RequestParser parser;
		auto request = parser.parseRequest(params);
		auto orders = _manager.processRequest(request);
		if (!orders.empty()) {
			OrderUtils::Normalize(orders);
			std::copy(orders.begin(), orders.end(), std::ostream_iterator<Order>(std::cout, " "));
			std::cout << std::endl;
		}
	}
	catch (RequestParserExeption& error) {
		std::cout << error.what() << std::endl;
	}
}

void CLIApplication::help() const
{
	static const std::vector<std::pair<const char*, std::vector<const char*>>> helpData =
	{
		{ "help", {"Provides help information."}},
		{ "exit", {"Quits the program."} },
		{ "<Trader Identifier> <Side> <Quantity> <Price>", {"Input request, where:",
									  "<Trader Identifier> is an alpha - numeric string.",
									  "<Side> is a single char: 'B' if this is a buy request, and 'S' if this is a sell request.",
									  "<Quantity> is an integer size of a request.",
									  "<Price> is an integer price of request."} }
	};

	auto const wle = std::strlen(std::max_element(std::begin(helpData), std::end(helpData),
				[](const std::pair<const char*, std::vector<const char*>>& a
				, const std::pair<const char*, std::vector<const char*>>& b)
				{
					return std::strlen(a.first) < std::strlen(b.first);
				}
				)->first);

	auto const column_width = wle + 1;

	for (auto row : helpData) {
		std::cout << row.first;
		for (auto iter = row.second.begin(); iter != row.second.end(); ++iter) {
			auto current_width = (iter == row.second.begin())? column_width - std::strlen(row.first) : column_width + 3;
			auto seperator = (iter == row.second.begin()) ? ':' : ' ';
			std::cout << std::left << std::setw(current_width) << std::setfill(' ') << ' ' << seperator << ' ' << *iter << std::endl;;
		}
	}
}
