#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set& s) : set(s) {
    first();
}

void SetIterator::first() {
    currentIndex = 0;
    current = nullptr;

    while (currentIndex < set.capacity && set.hashtable[currentIndex] == nullptr) {
        currentIndex++;
    }

    if (currentIndex < set.capacity) {
        current = set.hashtable[currentIndex];
    }
}

void SetIterator::next() {
    if (!valid()) {
        throw std::exception("Invalid iterator");
    }

    current = current->next;

    while (currentIndex < set.capacity && current == nullptr) {
        currentIndex++;
        if (currentIndex < set.capacity) {
            current = set.hashtable[currentIndex];
        }
    }
}

TElem SetIterator::getCurrent(){
    if (!valid()) {
        throw std::exception("No current element.");
    }

    return current->value;
}

bool SetIterator::valid() const {
    return currentIndex < set.capacity && current != nullptr;
}
