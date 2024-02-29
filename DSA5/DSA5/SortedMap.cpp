#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->r = r;
	capacity = 20;
	sizee = 0;
	this->elements = new TElem[capacity];
    this->right = new TValue[capacity];
    this->left = new TValue[capacity];
	root = -1;
	for (int i = 0; i < capacity; ++i) {
        elements[i] = NULL_TPAIR;
        right[i] = -1;
        left[i] = -1;
	}
}

void SortedMap::resize() {
    this->capacity = this->capacity * 2;
    TElem* new_elem = new TElem[this->capacity];
    TValue* new_right = new TValue[this->capacity];
    TValue* new_left = new TValue[this->capacity];
    for (int i = 0; i < this->sizee; i++)
    {
        new_elem[i] = this->elements[i];
        new_right[i] = this->right[i];
        new_left[i] = this->left[i];
    }
    for (int i = this->sizee; i < this->capacity; i++) {
        new_elem[i] = make_pair(0, 0);
        new_right[i] = -1;
        new_left[i] = -1;
    }
    this->elements = new_elem;
    this->right = new_right;
    this->left = new_left;
}

int SortedMap::getValueRange() const
{
    if (this->sizee == 0)
		return -1;

    int min = this->elements[0].second;
    int max = this->elements[0].second;

    for (int i = 1; i < this->sizee; i++)
	{
		if (this->elements[i].second < min)
			min = this->elements[i].second;
		if (this->elements[i].second > max)
			max = this->elements[i].second;
	}
    return max - min;
}


TValue SortedMap::add(TKey k, TValue v) {
    if (sizee >= capacity) {
        this->resize();
    }

    if (root == -1) {
        TElem NewData = make_pair(k, v);
        root = sizee;
        elements[root] = NewData;
        right[root] = -1;
        left[root] = -1;
        sizee++;
        return NULL_TVALUE;
    }

    int currentNodeIdx = root;
    int parentNodeIdx = -1;
    while (currentNodeIdx != -1) {
        TElem currentNode = elements[currentNodeIdx];
        if (k== currentNode.first) {
            TValue oldValue = currentNode.second;
            elements[currentNodeIdx].second = v;
            return oldValue;
        }
        parentNodeIdx = currentNodeIdx;
        if (r(k, currentNode.first))
            currentNodeIdx = this->left[currentNodeIdx];
        else
            currentNodeIdx = this->right[currentNodeIdx];
    }

    TElem NewData = make_pair(k, v);
    this->elements[sizee] = NewData;
    this->left[sizee] = -1;
    this->right[sizee] = -1;
    if (r(NewData.first, elements[parentNodeIdx].first))
        left[parentNodeIdx] = sizee;
    else
        right[parentNodeIdx] = sizee;
    sizee++;
    return NULL_TVALUE;



}

TValue SortedMap::search(TKey k) const {
    int current = root;
    while (current != -1) {
        if (elements[current].first == k) {
            return elements[current].second;
        }
        if (r(k, elements[current].first)) {
            current = left[current];
        }
        else {
            current = right[current];
        }
    }
    return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    int current = root;
    int parent = -1;
    while (current != -1 && elements[current].first != k) {
        parent = current;
        if (r(k, elements[current].first)) {
            current = left[current];
        }
        else {
            current = right[current];
        }
    }

    if (current == -1) {
        return NULL_TVALUE; //does not exist
    }

    TValue removedValue = elements[current].second;

    // Case 1: The node to be removed is a leaf node
    if (left[current] == -1 && right[current] == -1) {
        if (parent == -1) {
            // The node is the root and the only element in the map
            root = -1;
        }
        else if (left[parent] == current) {
            // The node is a left child of its parent
            left[parent] = -1;
        }
        else {
            // The node is a right child of its parent
            right[parent] = -1;
        }
    }
    // Case 2: The node to be removed has only one child
    else if (left[current] == -1 || right[current] == -1) {
        int child = (left[current] != -1) ? left[current] : right[current];
        if (parent == -1) {
            // The node is the root
            root = child;
        }
        else if (left[parent] == current) {
            // The node is a left child of its parent
            left[parent] = child;
        }
        else {
            // The node is a right child of its parent
            right[parent] = child;
        }
    }
    // Case 3: The node to be removed has two children
    else {
        int successor = right[current];
        int successorParent = current;
        while (left[successor] != -1) {
            successorParent = successor;
            successor = left[successor];
        }
        elements[current] = elements[successor];
        if (successorParent == current) {
            right[current] = right[successor];
        }
        else {
            left[successorParent] = right[successor];
        }
    }

    sizee--;
    return removedValue;
}

int SortedMap::size() const {
	return this->sizee;
}

bool SortedMap::isEmpty() const {
	if (this->sizee == 0)
		return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[] this->elements;
	delete[] this->left;
    delete[] this->right;
}
