#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "Key.h"

class HashTable {
private:
	static const int INIT_CAPACITY = 1000;
	struct TableEntry {
		bool		isEmpty;
		Key		location;
		std::string	contents;
		
		TableEntry()
		{
			isEmpty = true;
		}
		
		TableEntry(Key locInput, std::string stringInput)
		{
			isEmpty  = false;
			location = locInput;
			contents = stringInput;
		}
	};
	
	TableEntry	*stringTable;
	int		capacity;
	int		currSize;
	
	void	expand();
	size_t	hashValue(Key);
	
public:
	HashTable();
	~HashTable();
	
	void	insert(Key, std::string);
	void	print();
	void	print(Key);

};

#endif