#include "CLIApplication.h"

#include <iostream>

int main()
{
	auto cli = new CLIApplication();
	return cli->exec();
}
