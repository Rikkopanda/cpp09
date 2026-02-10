

// Include the stack library
#include <stack>
#include <variant>
#include <vector>
#include <deque>
#include <algorithm>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
	auto elements = makeGroups(this->numbers);

	printGroupTree(elements);

	main_pending_insertion_sort(elements);
}


void PmergeMe::add(int input)
{
	this->numbers.push_back(input);
};

void sortInts(std::vector<int>& v) {
	std::sort(v.begin(), v.end());
}

void printVec(const std::vector<int>& v) {
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i];
			if (i != v.size() - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
}

void PmergeMe::print()
{
	for (size_t i = 0; i < this->numbers.size(); i++)
	{
		std::cout << this->numbers[i] << " ";
	}
	std::cout << std::endl;
};
