
#include "RPN.hpp"

Rpn::Rpn() {}
Rpn::~Rpn() {}

// Include the stack library
#include <stack>

void Rpn::calculate(std::string input)
{
	std::cout << "Calculating RPN for input: " << input << std::endl;

	// Implement RPN calculation logic here

	this->data = 0.0f; // Placeholder result

	std::stack<float> values;

	std::istringstream iss(input);
	std::string token;
	while (iss >> token) {
		// if (token.find('(') != std::string::npos || token.find(')') != std::string::npos) {
		// 	std::cerr << "Error: brackets in input" << std::endl;
		// 	return;
				
		// }
		if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
			// Token is a number
			values.push(std::atof(token.c_str()));
		} else if (token == "+" || token == "-" || token == "*" || token == "/") {
			// Token is an operator
			if (values.size() < 2) {
				std::cerr << "Error: not enough values in the stack for operation " << token << std::endl;
				return;
			}
			float b = values.top(); values.pop();
			float a = values.top(); values.pop();
			float result;
			if (token == "+") result = a + b;
			else if (token == "-") result = a - b;
			else if (token == "*") result = a * b;
			else if (token == "/") {
				if (b == 0) {
					std::cerr << "Error: division by zero" << std::endl;
					return;
				}
				result = a / b;
			}
			values.push(result);
		}
	}

	if (values.size() != 1) {
		std::cerr << "Error: invalid RPN expression" << std::endl;
		return;
	}

	this->data = values.top();
	std::cout << "RPN result: " << this->data << std::endl;
}