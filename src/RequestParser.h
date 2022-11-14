#pragma once
#include "Request.h"

#include <string>
#include <vector>
#include <stdexcept>

class RequestParserExeption : public std::logic_error
{
public:
	RequestParserExeption(const char* what_arg)
		: std::logic_error(what_arg)
	{}
};

class RequestParser
{
public:
	Request::Ptr parseRequest(const std::string& input) const;

private:
	typedef std::vector<std::string> Tokens;
	void validate(const Tokens& params) const;
	void tokenize(const std::string& input, Tokens& tokens) const;
};

