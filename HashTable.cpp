#include <iostream>
#include <string>
#include <stdio.h>
#include <functional>
#include "HashTable.h"
#include "Key.h"
using namespace std;

HashTable::HashTable()
{
	capacity = INIT_CAPACITY;
	currSize = 0;
	
	stringTable = new TableEntry[capacity];
}

HashTable::~HashTable()
{
	delete []stringTable;
}

void HashTable::insert(Key keyToHash, string lineContents)
{
	expand();
	
	size_t index = hashValue(keyToHash) % capacity;
	
	TableEntry newEntry(keyToHash, lineContents);
	
	while(!stringTable[index].isEmpty)
		index = (index + 1) % capacity;
	
	stringTable[index] = newEntry;
	currSize++;
}

size_t HashTable::hashValue(Key keyToHash)
{
	std::hash<int> hasher;
	size_t hash1 = hasher(keyToHash.file);
	size_t hash2 = hasher(keyToHash.line);
	return hash1 ^(hash2 << 1);
}

void HashTable::expand()
{
	int loadFactor = currSize / capacity;
	if (loadFactor >= 0.7) {
		TableEntry *oldTable = stringTable;
		int oldTableSize     = capacity;
		capacity *= capacity;
		stringTable = new TableEntry[capacity];
		
		for (int i = 0; i < oldTableSize; i++) {
			if(!oldTable[i].isEmpty) {
				Key loc     = oldTable[i].location;
				string cont = oldTable[i].contents;
				insert(loc, cont);
			}
		}
		
		delete []oldTable;
	}
}

void HashTable::print()
{
	for (int i = 0; i < capacity; i++) {
		cout << i << ": ";
		
		if (stringTable[i].isEmpty)
			cout << "empty";
		else
			cout << "/" << stringTable[i].location.file
			     << ":" << stringTable[i].location.line
			     << " " << stringTable[i].contents;
		
		cout << endl;
	}
}

void HashTable::print(Key loc)
{
	size_t index = hashValue(loc) % capacity;

	// Checks for offset
	while(stringTable[index].location.file != loc.file or
	      stringTable[index].location.line != loc.line) {
		index = (index + 1) % capacity;
	}
	
	cout << stringTable[index].contents << endl;
}