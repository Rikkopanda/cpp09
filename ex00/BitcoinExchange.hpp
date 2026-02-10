#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cctype>

class Btc
{
private:
	std::map <std::string, float> data;
public:
	Btc();
	~Btc();
	void setData(std::string inputDate, float value);
	float getData(std::string data);
};