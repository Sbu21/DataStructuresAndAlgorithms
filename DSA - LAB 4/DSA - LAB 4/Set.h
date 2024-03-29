#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
typedef bool (*Condition)(TElem);
class SetIterator;

class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    private:
        struct Node {
            TElem value;
            Node* next;

            Node(TElem val) : value(val), next(nullptr) {}
        };

        int capacity;
        int count;
        Node** hashtable;

        int calculateHash(TElem elem) const;
        void resizeHashtable();

    public:
        //implicit constructor
        Set();

        void filter(Condition cond);

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        bool search(TElem elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;

        // destructor
        ~Set();

};





