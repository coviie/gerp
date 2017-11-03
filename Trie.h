/*
 *  Trie.h
 *  Trie Class Header and Definition
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Trie data structure that stores words; terminating character of each word
 *  is a Key struct that stores where the word was located, and the contents
 *  of the line that contained the word.
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <vector>
#include "Key.h"

class Trie {
public:
	/******************************** 
	 * Constructors and Destructors *
	 ********************************/
	// Initializes an empty Trie
	Trie();
	
	// Destructor that destroys heap-allocated data
	~Trie();
	
	/******************************** 
	 *         Add Functions        *
	 ********************************/
	// Adds the given word (and the relevant Key) 
	void addWord(std::string, Key);
	
	/******************************** 
	 *        Search Functions      *
	 ********************************/
	// Searches for the given word; case-sensitive
	std::vector<Key> searchSensitive(std::string);
	
	// Searches for the given word; case-insensitive
	std::vector<Key> searchInsensitive(std::string);
	
	/******************************** 
	 *        Print Functions       *
	 ********************************/
	// Prints all the contents in the Trie
	void printTrie();

private:
	/******************************** 
	 *        Trie Variables        *
	 ********************************/
	// Size of each children-array at each level of Trie*
	static const int ASCII_LENGTH = 94;
	
	// Offset (to correct a given ASCII value)
	static const int OFFSET = 33;
	
	/******************************** 
	 *          Node Struct         *
	 ********************************/
	// Node struct that contains the char, a vector of keys and a 
	// children-array
	struct Node {
		char			c;
		std::vector<Key>	keys;
		Node			*children[ASCII_LENGTH];
		
		// Default Node constructor (if nothing was provided)
		Node() {
			c  = ' ';
			
			for (int i = 0; i < ASCII_LENGTH; i++)
				children[i] = NULL;
		}
		
		// Node constructor that stores the given input
		Node(char input) {
			c  = input;
			
			for (int i = 0; i < ASCII_LENGTH; i++)
				children[i] = NULL;
		}
	};
	
	// Root
	Node *root;
	
	/******************************** 
	 *        Helper Functions      *
	 ********************************/
	// Destructor helper function
	void clear(Node*);

	// printTrie helper function
	void printNode(Node*, std::string);
	
	// Checks if an existing key already exists in the given Node
	bool keyExists(Node*, Key);
	
	// Converts the ASCII value into one that fits the 94-length array
	int convertASCII(int);
	
	// Insensitive search helper function
	std::vector<Key> searchInsensitive(Node*, std::string);
};

#endif