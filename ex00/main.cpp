#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include "BitcoinExchange.hpp"

int exctractStringsFromOneLine(
	std::string line,
	std::string &date,
	std::string &exchange_date,
	std::string delimiter
)
{
	size_t pos = line.find(delimiter);
	if (pos == std::string::npos)
		return -1;
	date = line.substr(0, pos);
	exchange_date = line.substr(pos + delimiter.length());
	// std::cout << date.c_str() << "\n" << std::endl;
	// std::cout << exchange_date.c_str() << "\n" << std::endl;
	return 0;
}


void readFileIntoDatabase(Btc &btc, const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::string date;
		std::string exchange_date;
		if (exctractStringsFromOneLine(line, date, exchange_date, ",") == -1)
			continue;
		float value;
			try {
			value = std::atof(exchange_date.c_str());
        } catch (std::exception &a) {
			(void)a;
            std::cerr << "Error: could not parse value" << std::endl;
            continue;
        }
		btc.setData(date, value);
		std::cout << " again what value?: " << btc.getData(date) << "\n" << std::endl;
	}
	file.close();
}

void handleInputMultiplyAndOutput(Btc &btc, const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::string date;
		std::string value_str;
		exctractStringsFromOneLine(line, date, value_str, " | ");
		float value = std::atof(value_str.c_str());
		float rate = btc.getData(date);
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		else if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		else if (rate != -1.0f) // assuming -1.0f indicates not found
		{
			float result = rate * value;
			std::cout << date << " => " << value << " = " << result << std::endl;
		}
		else
		{
			std::cout << "No exchange rate found for date: " << date << std::endl;
		}
	}
	file.close();
}

int main (int args, char *argv[])
{
	if (args != 2)
		return 1;
	std::cout << (argv[1]) << std::endl;

	Btc btc;
	readFileIntoDatabase(btc, "data.csv");

	handleInputMultiplyAndOutput(btc, argv[1]);

	return 0;
}
