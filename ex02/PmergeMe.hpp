#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <variant>
#include <utility>
#include <type_traits>
#include <algorithm>

using IntOrPair = std::variant<int, std::pair<int, int>>;
extern std::vector<IntOrPair> vec;

void sortInts(std::vector<int>& v);
void sortPairsBySecond(std::vector<IntOrPair>& v);
void printVec(const std::vector<IntOrPair>& v);
void printVec(const std::vector<int>& v);
void make_main_and_pending_sequences(std::vector<int>& main_sequence, std::vector<int>& pending_sequence);

template<typename T>
void printVecPair(const std::vector<std::pair<T, T>>& v) {
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << "(" << v[i].first << ", " << v[i].second << ")";
			if (i != v.size() - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
}

// template<typename T>
// void printVecPair(const std::vector<T>& v) {
// 		for (size_t i = 0; i < v.size(); ++i) {
// 			std::cout << "(" << v[i] ")";
// 			if (i != v.size() - 1)
// 				std::cout << ", ";
// 		}
// 		std::cout << std::endl;
// }

template<typename T>
std::vector<std::pair<T, T>> makePairs(std::vector<T>& elements)
{
	std::vector<std::pair<T, T>> return_vec;
	for (size_t i = 0; i < elements.size(); i += 2)
	{
		if (i + 1 < elements.size())
		{
			T first = elements[i];
			T second = elements[i + 1];
			if (first > second)
				std::swap(first, second);
			return_vec.push_back(std::make_pair(first, second));
		}
		else
		{
			return_vec.push_back(std::make_pair(elements[i], elements[i]));
		}
	}
	return return_vec;
}

class PmergeMe
{
private:
	std::vector<int> numbers;
public:
	PmergeMe();
	~PmergeMe();
	void makeFirstPairs();
	template<typename T> void sort();
	void add(int input);
	void print();
};

template<typename T>
void printi(const T& value) {
    std::cout << value;
}

template<typename A, typename B>
void printi(const std::pair<A, B>& p) {
    std::cout << "(";
    printi(p.first);
    std::cout << ", ";
    printi(p.second);
    std::cout << ")";
}

template<typename T>
void PmergeMe::sort()
{
	static_assert(std::is_same<T, int>::value, "PmergeMe stores int only");

	// makeFirstPairs();
	// std::vector<std::pair<T, T>> pairs = makePairs(this->numbers);
	auto pairs = makePairs(this->numbers);

	for (const auto& x : pairs) {
		printi(x);
		std::cout << "; ";
	}
	std::cout << std::endl;

	auto pairs2 = makePairs(pairs);
	for (const auto& x : pairs2) {
		printi(x);
		std::cout << "\033[33m";
		std::cout << "_____";
		std::cout << "\033[0m";
	}
	std::cout << std::endl;

	auto pairs3 = makePairs(pairs2);
	// printVecPair(pairs2);
	// std::cout << "pairs2: " << std::endl;
	// std::cout << pairs2[0] << std::endl;

	for (const auto& x : pairs3) {
		printi(x);
		std::cout << "\033[33m";
		std::cout << "_____";
		std::cout << "\033[0m";
	}
	std::cout << std::endl;


	// std::vector<int> main_sequence;
	// std::vector<int> pending_sequence;

	// make_main_and_pending_sequences(main_sequence, pending_sequence);

	// std::cout << "vec contents: ";
	// printVec(vec);
	// sortPairsBySecond(vec);
	// std::cout << "sorted vec contents: ";
	// printVec(vec);

	// sortInts(main_sequence);
	// for (const auto& value : pending_sequence) {
	// 	std::vector<int>::const_iterator pos = std::lower_bound(main_sequence.begin(), main_sequence.end(), value);
	// 	main_sequence.insert(pos, value);
	// }
	// std::cout << "main sequence: ";
	// printVec(main_sequence);
}
