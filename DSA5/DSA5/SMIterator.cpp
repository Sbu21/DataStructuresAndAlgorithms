#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->current = -1;
	int node = map.root;
	while (node != -1) {
		stack.push_back(node);
		node = map.left[node];
	}
	if (!stack.empty()) {
		current = stack.back();
	}
}

void SMIterator::first(){
	stack.clear();

	int node = map.root;
	while (node != -1) {
		stack.push_back(node);
		node = map.left[node];
	}

	if (!stack.empty()) {
		current = stack.back();
	}
	else {
		current = -1;
	}
}

void SMIterator::next(){
	if (!valid())
		throw std::runtime_error("Invalid iterator!");

	int node = stack.back();
	stack.pop_back();

	if (map.right[node] != -1) {
		node = map.right[node];
		while (node != -1) {
			stack.push_back(node);
			node = map.left[node];
		}
	}

	if (!stack.empty()) {
		current = stack.back();
	}
	else {
		current = -1;
	}
}

bool SMIterator::valid() const{
	return current != -1;
}

TElem SMIterator::getCurrent() const{
	if (!valid()) {
		throw std::exception("Invalid iterator!");
	}
	return map.elements[current];
}


