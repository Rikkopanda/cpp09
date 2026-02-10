

// Include the stack library
#include <stack>
#include <variant>
#include <vector>
#include <deque>
#include <algorithm>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::add(int input)
{
	this->numbers.push_back(input);
};

void sortInts(std::vector<int>& v) {
	std::sort(v.begin(), v.end());
}

std::vector<IntOrPair> vec;

void printVec(const std::vector<IntOrPair>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		if (std::holds_alternative<int>(v[i])) {
			std::cout << "[int] " << std::get<int>(v[i]);
		} else if (std::holds_alternative<std::pair<int, int>>(v[i])) {
			std::pair<int, int> p = std::get<std::pair<int, int>>(v[i]);
			std::cout << "[pair] (" << p.first << ", " << p.second << ")";
		}
		if (i != v.size() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

void printVec(const std::vector<int>& v) {
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i];
			if (i != v.size() - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
}

void sortPairsBySecond(std::vector<IntOrPair>& v) {
	// Collect indices and pairs
	std::vector<std::pair<size_t, std::pair<int, int>>> pairs;
	for (size_t i = 0; i < v.size(); ++i) {
		if (std::holds_alternative<std::pair<int, int>>(v[i])) {
			pairs.push_back({i, std::get<std::pair<int, int>>(v[i])});
		}
	}
	// Sort pairs by .second
	std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return a.second.second < b.second.second;
	});
	// Place sorted pairs back in their original positions
	size_t pairIdx = 0;
	for (size_t i = 0; i < v.size(); ++i) {
		if (std::holds_alternative<std::pair<int, int>>(v[i])) {
			v[i] = pairs[pairIdx++].second;
		}
	}
}

void PmergeMe::makeFirstPairs()
{
	for (size_t i = 0; i < this->numbers.size(); )
	{
		// make pairs of two. Sort the pair. Put it in vec. Add single int if odd number of ints
		if (i + 1 < this->numbers.size())
		{
			int first = this->numbers[i];
			int second = this->numbers[i + 1];
			if (first > second)
				std::swap(first, second);
			vec.push_back(std::make_pair(first, second));
			i += 2;
		}
		else
		{
			vec.push_back(this->numbers[i]);
			i += 1;
		}
	}
}

void make_main_and_pending_sequences(std::vector<int>& main_sequence, std::vector<int>& pending_sequence) {
	//push first element to main sequence
	// what holds_alternative does ; checks if vec[0] is int or pair
	if (std::holds_alternative<int>(vec[0])) {
		main_sequence.push_back(std::get<int>(vec[0]));
	} else if (std::holds_alternative<std::pair<int, int>>(vec[0])) {
		auto p = std::get<std::pair<int, int>>(vec[0]);
		main_sequence.push_back(p.first);
		main_sequence.push_back(p.second);
	}
	//iterate through rest of vec, build main and pending sequences
	for (size_t i = 1; i < vec.size(); i++) {
		if (std::holds_alternative<int>(vec[i])) {
			main_sequence.push_back(std::get<int>(vec[i]));
		} else if (std::holds_alternative<std::pair<int, int>>(vec[i])) {
			auto p = std::get<std::pair<int, int>>(vec[i]);
			main_sequence.push_back(p.second);
			pending_sequence.push_back(p.first);
		}
	}
}

// template<typename T>
// struct PairGroup {
//     using type = std::pair<T, T>;
// };

void PmergeMe::print()
{
	for (size_t i = 0; i < this->numbers.size(); i++)
	{
		std::cout << this->numbers[i] << " ";
	}
	std::cout << std::endl;
};
