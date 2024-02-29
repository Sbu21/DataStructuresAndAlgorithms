#pragma once
#include "SortedMap.h"
#include <iostream>
#include <vector>
using namespace std;
//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	int current;
	vector<int> stack;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

