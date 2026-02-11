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
#include <memory>
#include <type_traits>
#include <algorithm>

// using IntOrPair = std::variant<int, std::pair<int, int>>;
// extern std::vector<IntOrPair> vec;

void sortInts(std::vector<int>& v);
// void sortPairsBySecond(std::vector<IntOrPair>& v);
// void printVec(const std::vector<IntOrPair>& v);
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
			return_vec.push_back(std::make_pair(elements[i], T()));
		}
	}
	return return_vec;
}

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node {
	bool is_leaf;
	NodePtr PairWith;
	int value;
	NodePtr left;
	NodePtr right;
	bool remaining; // for odd number of elements

	explicit Node(int v)
		: is_leaf(true), value(v), left(NULL), right(NULL), remaining(false) {}

	Node(const NodePtr& l, const NodePtr& r)
		: is_leaf(false), value(0), left(l), right(r), remaining(false) {}
};

inline NodePtr makeLeaf(int v) {
	return NodePtr(new Node(v));
}

inline NodePtr makePairNode(const NodePtr& left, const NodePtr& right) {
	return NodePtr(new Node(left, right));
}

inline void printNode(const NodePtr& node)
{
	if (!node) {
		std::cout << "_";
		return;
	}
	if (node->is_leaf) {
		std::cout << node->value;
		return;
	}
	std::cout << "(";
	printNode(node->left);
	std::cout << ", ";
	printNode(node->right);
	std::cout << ")";
}

inline void printGroup(const std::vector<NodePtr>& elements)
{
	for (size_t i = 0; i < elements.size(); ++i) {
		printNode(elements[i]);
		if (i + 1 < elements.size())
			std::cout << " | ";
	}
	std::cout << std::endl;
}

inline std::vector<NodePtr> makeNodePairs(const std::vector<NodePtr>& elements)
{
	std::vector<NodePtr> return_vec;
	for (size_t i = 0; i < elements.size(); i += 2)
	{
		if (i + 1 < elements.size())
		{
			NodePtr first = elements[i];
			NodePtr second = elements[i + 1];
			first->PairWith = second;
			second->PairWith = first;
			if (first->is_leaf && second->is_leaf)
			{
				std::cout << "Leaf: " << first->value << " vs " << second->value << std::endl;
				if (first->value > second->value)
					std::swap(first, second);
				std::cout << "biggest leaf: " << second->value << std::endl;
			}
			else
			{
				std::cout << "Node: " << first->value << " vs " << second->value << std::endl;		
				if (first->value > second->value)
					std::swap(first, second);
				std::cout << "biggest node: " << second->value << std::endl;
			}

			NodePtr new_node = makePairNode(first, second);
			new_node->value = second->value; // store
			return_vec.push_back(new_node);
		}
		else
		{
			NodePtr new_node = makePairNode(elements[i], NULL);
			new_node->remaining = true; // mark as remaining
			return_vec.push_back(new_node);

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
	void sort();
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

inline std::vector<NodePtr> makeGroups(const std::vector<NodePtr>& elements)
{
	if (elements.size() <= 2) {
		return elements;
	}
	std::vector<NodePtr> pair = makeNodePairs(elements);
	printGroup(pair);

	std::vector<NodePtr> groups = makeGroups(pair);
	// printGroup(groups);

	return groups;
}

inline std::vector<NodePtr> makeGroups(std::vector<int>& elements)
{
	std::vector<NodePtr> leaves;
	leaves.reserve(elements.size());
	for (size_t i = 0; i < elements.size(); ++i) {
		leaves.push_back(makeLeaf(elements[i]));
	}
	return makeGroups(leaves);
}



inline void printGroupTree(const std::vector<NodePtr>& groups) {
	if (groups[0]->is_leaf) {
		std::cout << "Final sorted sequence: ";
		printGroup(groups);
		return;
	}
	if (groups[0]->left)
		printGroupTree({groups[0]->left});
	if (groups[0]->right)
		printGroupTree({groups[0]->right});
}

inline int jacobStallNum(int n) {
	if (n == 0) return 1;
	if (n == 1) return 1;
	return jacobStallNum(n - 1) + jacobStallNum(n - 2);
}

inline std::vector<NodePtr> jacobStallOrder(const std::vector<NodePtr>& groups) {
	std::vector<NodePtr> order;

	order.push_back(groups[0]);
	size_t previous_index = 0;
	std::cout << "Jacob-Stall order: " << groups[0]->value << " at index 0" << std::endl;
	for (size_t i = 1; i < groups.size(); ++i)
	{
		std::cout << "i = " << i << std::endl;
		size_t index = jacobStallNum(i + 2) - 1; // -1 for 0-based index, + 2 because Jacob-Stall numbers start with J(0) = 1, J(1) = 1
		while (index > previous_index) {
			if (index < groups.size()) {
				std::cout << "Jacob-Stall order: " << groups[index]->value << " at index " << index << std::endl;
				order.push_back(groups[index]);
			}
			index--;
		}
		if (groups.size() == order.size())
			break;
		previous_index = jacobStallNum(i + 2) - 1; // update previous_index to the last index added
	}
	return order;
}

inline void main_pending_insertion_sort(const std::vector<NodePtr>& groups) {
	printGroup(groups);
	// std::vector<NodePtr> main_sequence = groups[0]->left
	// if (groups[0])
	if (groups.size() <= 1) {
		printGroup(groups);
		std::vector<NodePtr> split_groups;
		for (unsigned long i = 0; i < groups.size(); ++i) {
			if (groups[i]->left)
				split_groups.push_back(groups[i]->left);
			if (groups[i]->right)
				split_groups.push_back(groups[i]->right);
		}
		main_pending_insertion_sort(split_groups);
		return;
	}
	else
	{
		std::vector<NodePtr> main_sequence;
		std::vector<NodePtr> pending_sequence;
		std::vector<NodePtr> remaining_sequence;

		if (groups[0]->left)
			main_sequence.push_back(groups[0]->left);
		if (groups[0]->right)
			main_sequence.push_back(groups[0]->right);
		for (unsigned long i = 1; i < groups.size(); ++i) {
			if (!groups[i]->left || !groups[i]->right) {
				std::cout << "remaining: " << groups[i]->value << std::endl;
				if (groups[i]->left)
					remaining_sequence.push_back(groups[i]->left);
				else
					remaining_sequence.push_back(groups[i]->right);
				continue;
			}
			if (groups[i]->left)
				pending_sequence.push_back(groups[i]->left);
			if (groups[i]->right)
				main_sequence.push_back(groups[i]->right);
		}
		std::cout << "main sequence: ";
		printGroup(main_sequence);
		std::cout << "pending sequence: ";
		printGroup(pending_sequence);
		std::cout << "remaining sequence: ";
		printGroup(remaining_sequence);
		if (main_sequence[0]->is_leaf) {
			for (unsigned long i = 0; i < remaining_sequence.size(); ++i) {
				std::cout << "main sequence leaf: " << remaining_sequence[i]->value << std::endl;
				pending_sequence.push_back(remaining_sequence[i]);
			}
		}
		else
		{
			for (unsigned long i = 0; i < remaining_sequence.size(); ++i) {
				main_sequence.push_back(remaining_sequence[i]);
			}
		}
		std::vector<NodePtr> jacobStallOrderedList = jacobStallOrder(pending_sequence);
		
		for (unsigned long i = 0; i < jacobStallOrderedList.size(); ++i) {
			NodePtr value = jacobStallOrderedList[i];
			// find PairWith in main_sequence and insert value in range before it
			NodePtr pairWith = value->PairWith;
			auto end_bound = std::find(main_sequence.begin(), main_sequence.end(), pairWith);
			std::cout << "inserting " << value->value << " before " << pairWith->value << std::endl;
			auto pos = std::lower_bound(main_sequence.begin(), end_bound, value, [](const NodePtr& a, const NodePtr& b) {
				return a->value < b->value;
			});
			main_sequence.insert(pos, value);
		}
		printGroup(main_sequence);
		if (main_sequence[0]->is_leaf) {
			std::cout << "Final sorted sequence: ";
			printGroup(main_sequence);
			return;
		}
		main_pending_insertion_sort(main_sequence);
	}
}
