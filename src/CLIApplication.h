#pragma once
#include "Manager.h"

#include <iostream>

class CLIApplication 
{
public:
	int exec();

private:

	struct Command {
		enum class Type : unsigned {
			Exit,
			Help,
			Input
		};
		std::string params;
		Type type = Type::Input;
	};
	Command readCommand() const;
	
	void input(const std::string& params);
	void help() const;
private:
	Manager _manager;
};
