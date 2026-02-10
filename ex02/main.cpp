#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "PmergeMe.hpp"
#include <stack>

int main (int args, char *argv[])
{
	if (args != 2)
	{
		std::cout << "put one argument, put string in quotes" << std::endl;
		return 1;
	}
	PmergeMe lijst;
	std::istringstream iss(argv[1]);
	std::string element;
	while (iss >> element)
	{
		// std::cout << iss << std::endl;
		std::cout << "elem " << element << std::endl;
		if (!std::isdigit(element[0]))
		{
			std::cout << "put only digits" << std::endl;
			return 1;
		}
		lijst.add(std::atoi(element.c_str()));
	}
	// lijst.print();
	lijst.sort<int>();
	return 0;
}
