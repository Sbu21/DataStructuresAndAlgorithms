#include "Set.h"
#include "SetIterator.h"
#include <cmath>

Set::Set() {
    capacity = 10;
    count = 0;
    hashtable = new Node * [capacity]();
}

void Set::filter(Condition cond)
{
for (int i = 0; i < capacity; i++) {
		Node* current = hashtable[i];
		while (current != nullptr) {
			Node* next = current->next;
			if (!cond(current->value)) {
				remove(current->value);
			}
			current = next;
		}
	}
}

int Set::calculateHash(TElem elem) const {
    return abs(elem) % capacity;
}

void Set::resizeHashtable() {
    int newCapacity = capacity * 2;
    Node** newHashtable = new Node * [newCapacity] {};

    for (int i = 0; i < capacity; i++) {
        Node* current = hashtable[i];
        while (current != nullptr) {
            Node* next = current->next;
            int newIndex = abs(current->value) % newCapacity;
            current->next = newHashtable[newIndex];
            newHashtable[newIndex] = current;
            current = next;
        }
    }

    capacity = newCapacity;
    delete[] hashtable;
    hashtable = newHashtable;
}

bool Set::add(TElem elem) {
    int index = calculateHash(elem);
    Node* current = hashtable[index];

    while (current != nullptr) {
        if (current->value == elem) {
            return false;  
        }
        current = current->next;
    }

    Node* newNode = new Node(elem);
    newNode->next = hashtable[index];
    hashtable[index] = newNode;

    count++;

    if (count > capacity * 2) {
        resizeHashtable();
    }

    return true;
}

bool Set::remove(TElem elem) {
    int index = calculateHash(elem);
    Node* current = hashtable[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->value == elem) {
            if (prev == nullptr) {
                hashtable[index] = current->next;
            }
            else {
                prev->next = current->next;
            }

            delete current;
            count--;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

bool Set::search(TElem elem) const {
    int index = calculateHash(elem);
    Node* current = hashtable[index];

    while (current != nullptr) {
        if (current->value == elem) {
            return true;
        }
        current = current->next;
    }

    return false;
}

int Set::size() const {
    return count;
}

bool Set::isEmpty() const {
    return count == 0;
}

SetIterator Set::iterator() const {
    return SetIterator(*this);
}

Set::~Set() {
    for (int i = 0; i < capacity; i++) {
        Node* current = hashtable[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] hashtable;
}
