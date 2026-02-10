
#include "BitcoinExchange.hpp"

Btc::Btc() {}
Btc::~Btc() {}

void Btc::setData(std::string inputDate, float value)
{
	this->data.insert(std::make_pair(inputDate, value));
}

float Btc::getData(std::string input_data)
{
	// Try to find exact match
	std::map<std::string, float>::iterator it = this->data.find(input_data);
	if (it != this->data.end())
		return it->second;

	// If not found, find closest lower date
	it = this->data.lower_bound(input_data);
	if (it == this->data.begin())
		return -1.0f; // No lower date exists
	--it; // Move to the previous (lower) date
	return it->second;
}
