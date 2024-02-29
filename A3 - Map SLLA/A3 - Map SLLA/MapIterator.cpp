#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->currentNode = this->map.head;
}


void MapIterator::first() {
	this->currentNode = this->map.head;
}


void MapIterator::next() {
	if (!this->valid())
	{
		throw exception();
	}
	this->currentNode = this->map.nodes[this->currentNode].next;
}


TElem MapIterator::getCurrent(){
	if (!this->valid())
	{
		throw exception();
	}
	return this->map.nodes[this->currentNode].info;
}


bool MapIterator::valid() const {
	if (this->currentNode == -1)
	{
		return false;
	}
	return true;
}

void MapIterator::jumpForward(int k)
{
	if (k < 0)
	{
		throw exception();
	}
	if (k == 0)
	{
		return;
	}
	if (this->currentNode == -1)
	{
		throw exception();
	}
	int i = 0;
	while (i < k && this->valid())
	{
		this->next();
		i++;
	}
	if (i < k)
	{
		throw exception();
	}
}



