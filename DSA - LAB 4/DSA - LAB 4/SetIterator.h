#pragma once
#include "Set.h"

class SetIterator {
    // Friend class Set
    friend class Set;

private:
    const Set& set;
    Set::Node* current;
    int currentIndex;

    SetIterator(const Set& s);

public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
};
