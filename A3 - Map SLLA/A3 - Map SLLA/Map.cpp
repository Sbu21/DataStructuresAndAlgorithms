#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->capacity = 10;
	this->length = 0;
	this->head = -1;
	this->firstEmpty = 0;
	this->nodes = new sllaNode[this->capacity];
	for (int i = 0; i < this->capacity - 1; i++)
	{
		this->nodes[i].next = i + 1;
	}
	this->nodes[this->capacity - 1].next = -1;
}

Map::~Map() {
	delete[] this->nodes;
}

TValue Map::add(TKey c, TValue v){
	if (this->capacity == this->length)
	{
		this->capacity *= 2;
		sllaNode* newNodes = new sllaNode[this->capacity];
		for (int i = 0; i < this->length; i++)
		{
			newNodes[i] = this->nodes[i];
		}
		for (int i = this->length; i < this->capacity - 1; i++)
		{
			newNodes[i].next = i + 1;
		}
		this->firstEmpty = this->length;
		newNodes[this->capacity - 1].next = -1;
		this->nodes = newNodes;
	}
	if (this->length == 0)
	{
		this->nodes[firstEmpty].info.first = c;
		this->nodes[firstEmpty].info.second = v;
		this->firstEmpty = this->nodes[firstEmpty].next;
		this->nodes[this->head].next = firstEmpty;
		this->head = 0;
		this->length++;
		return NULL_TVALUE;
	}
	else
	{
		int currentNode = this->head;
		while (currentNode != -1)
		{
			if (this->nodes[currentNode].info.first == c)
			{
				TValue oldValue = this->nodes[currentNode].info.second;
				this->nodes[currentNode].info.second = v;
				return oldValue;
			}
			currentNode = this->nodes[currentNode].next;
		}
		this->nodes[firstEmpty].info.first = c;
		this->nodes[firstEmpty].info.second = v;
		this->nodes[firstEmpty - 1].next = firstEmpty;
		this->firstEmpty = this->nodes[firstEmpty].next;
		this->length++;
		return NULL_TVALUE;
	}
}

TValue Map::search(TKey c) const{
	int currentNode = this->head;
	while (currentNode != -1)
	{
		if (this->nodes[currentNode].info.first == c)
		{
			return this->nodes[currentNode].info.second;
		}
		currentNode = this->nodes[currentNode].next;
	}
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	if (this->head == -1)
	{
		return NULL_TVALUE;
	}
	else
	{
		int currentNode = this->head;
		int previousNode = -1;
		while (currentNode != -1 && this->nodes[currentNode].info.first != c)
		{
			previousNode = currentNode;
			currentNode = this->nodes[currentNode].next;
		}
		if (currentNode == -1)
		{
			return NULL_TVALUE;
		}
		else
		{
			TValue oldValue = this->nodes[currentNode].info.second;
			if (currentNode == this->head)
			{
				this->head = this->nodes[this->head].next;
			}
			else
			{
				this->nodes[previousNode].next = this->nodes[currentNode].next;
			}
			this->nodes[currentNode].next = this->firstEmpty;
			this->firstEmpty = currentNode;
			this->length--;
			return oldValue;
		}
	}
}


int Map::size() const {
	return this->length;
}

bool Map::isEmpty() const{
	return this->length == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



