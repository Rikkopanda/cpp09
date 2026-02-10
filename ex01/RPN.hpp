#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cctype>

class Rpn
{
private:
	float data;
public:
	Rpn();
	~Rpn();
	void calculate(std::string input);
};