#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "RPN.hpp"

int main (int args, char *argv[])
{
	if (args != 2)
	{
		std::cout << "put one argument, put string in quotes" << std::endl;
		return 1;
	}
	std::cout << (argv[1]) << std::endl;

	Rpn Rpn;
	Rpn.calculate(argv[1]);
	return 0;
}
