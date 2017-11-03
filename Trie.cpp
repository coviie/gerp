/*
 *  Trie.cpp
 *  Trie Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Trie data structure that stores words; terminating character of each word
 *  is a Key struct that stores where the word was located, and the contents
 *  of the line that contained the word.
 */

#include <iostream>
#include <vector>
#include <string>
#include "Trie.h"
#include "Key.h"
using namespace std;

/*******************************
 *  Constructors & Destructors *
 *******************************/
/* [Name]:		Trie
 * [Purpose]:		Constructor; Initializes an empty Trie
 * [Parameters]:	-
 * [Returns]:		-
 */
Trie::Trie()
{
	root = new Node();
}

/* [Name]:		~Trie
 * [Purpose]:		Destructor; Recursively deletes data in each Node
 * 			of the Trie-array.
 * [Parameters]:	-
 * [Returns]:		-
 */
Trie::~Trie()
{
	clear(root);
}

/* [Name]:		clear
 * [Purpose]:		Destructor helper function; Recursively deletes data in 
 * 			each Node of the Trie-array.
 * [Parameters]:	Node* (Node to start clearing from)
 * [Returns]:		void
 */
void Trie::clear(Node *tmp)
{
	if (tmp != NULL) {
		for (int i = 0; i < ASCII_LENGTH; i++) {
			if (tmp->children[i] != NULL) 
				clear(tmp->children[i]);
		}
		delete tmp;
	}
}

/*******************************
 *            Adding           *
 *******************************/
/* [Name]:		addWord
 * [Purpose]:		Adds the given word into the Trie (and the Key
 * 			that contains the file info as the terminating
 * 			character)
 * [Parameters]:	1 string (word to add), 1 Key (file+line info &
 * 			data)
 * [Returns]:		void
 */
void Trie::addWord(string word, Key location) 
{
	Node *tmp = root;
	
	for (size_t i = 0; i < word.length(); i++) {
		int asciiVal = convertASCII(int(word[i]));
		
		if (tmp->children[asciiVal] != NULL) {
			tmp = tmp->children[asciiVal];
		}
		
		else {
			Node *newNode = new Node(word[i]);
			tmp->children[asciiVal] = newNode;	
			tmp = tmp->children[asciiVal];
		}
	}
	
	if (word.length() > 0 and !keyExists(tmp, location))
		tmp->keys.push_back(location);
}

/* [Name]:		keyExists
 * [Purpose]:		Checks if an existing key already exists
 * [Parameters]:	1 Node* (terminating character Node),
 * 			1 Key (check if a duplicate of this key exists)
 * [Returns]:		bool (true if duplicate exists, false if not)
 */
bool Trie::keyExists(Node *aNode, Key location)
{
	if (!aNode->keys.empty()) {
		if (aNode->keys.back().file == location.file and
		    aNode->keys.back().line == location.line)
			return true;
	}
		
	return false;
}

/* [Name]:		convertASCII
 * [Purpose]:		Converts the ASCII of the given char into one that
 * 			fits the 94-length array
 * [Parameters]:	1 int (ascii to be converted)
 * [Returns]:		int (converted ASCII)
 */
int Trie::convertASCII(int asciiVal) 
{
	asciiVal -= OFFSET;
	return asciiVal;
}

/*******************************
 *           Searching         *
 *******************************/
/* [Name]:		searchSensitive
 * [Purpose]:		Searches for the given word; case-sensitive
 * [Parameters]:	1 string (word to search for)
 * [Returns]:		vector<Key> (vector of Keys that store where the
 * 			word is located)
 */
vector<Key> Trie::searchSensitive(string word)
{
	Node *tmp = root;
	vector<Key> empty;
	for (size_t i = 0; i < word.length(); i++) {
		int asciiVal = convertASCII(int(word[i]));
		
		if (tmp->children[asciiVal] != NULL)
			tmp = tmp->children[asciiVal];
		
		else
			return empty;
	}

	if (!tmp->keys.empty())
		return tmp->keys;
	else
		return empty;
}

/* [Name]:		searchInsensitive
 * [Purpose]:		Searches for the given word; case-insensitive
 * [Parameters]:	1 string (word to search for)
 * [Returns]:		vector<Key> (vector of Keys that store where the
 * 			word is located)	
 */
vector<Key> Trie::searchInsensitive(string word)
{
	return searchInsensitive(root, word);
}

/* [Name]:		searchInsensitive
 * [Purpose]:		Helper function for searchInsensitive
 * [Parameters]:	1 Node* (Node to look at), 1 string (word to 
 * 			search for)
 * [Returns]:		vector<Key> (vector of Keys that store where the
 * 			word is located)	
 */
vector<Key> Trie::searchInsensitive(Node* aNode, string word)
{
	if (word == "")
		return aNode->keys;
	vector<Key> keyList;
	string aWord = word.substr(1, string::npos);
	int upperASCII = convertASCII(toupper(word[0]));
	int lowerASCII = convertASCII(tolower(word[0]));
	int intASCII   = convertASCII(word[0]);
	if (isalpha(word[0])) {
		if (aNode->children[lowerASCII] != NULL) {
			Node *lowerChar = aNode->children[lowerASCII];
			vector<Key> tmp = searchInsensitive(lowerChar, aWord);
			keyList.insert(keyList.end(), tmp.begin(), tmp.end());
		}
		
		if (aNode->children[upperASCII] != NULL) {
			Node *upperChar = aNode->children[upperASCII];
			vector<Key> tmp = searchInsensitive(upperChar, aWord);
			keyList.insert(keyList.end(), tmp.begin(), tmp.end());
		}
	}
	else {
		if (aNode->children[intASCII] != NULL) {
			Node *intChar = aNode->children[intASCII];
			vector<Key> tmp = searchInsensitive(intChar, aWord);
			keyList.insert(keyList.end(), tmp.begin(), tmp.end());
		}
	}
	return keyList;
}

/*******************************
 *           Printing          *
 *******************************/
/* [Name]:		printTrie
 * [Purpose]:		Prints all contents of the Trie;
 * 			(used for debugging)
 * [Parameters]:	-
 * [Returns]:		void
 */
void Trie::printTrie()
{
        printNode(root, "");
}

/* [Name]:		printNode
 * [Purpose]:		Prints a contents of the Trie, starting from
 * 			the given Node
 * [Parameters]:	1 Node* (Node to start printing from), 1 string
 * 			(prefix; helps to ensure all words are fully
 * 			printed)
 * [Returns]:		void
 */
void Trie::printNode(Node* aNode, string prefix)
{
	if (aNode != NULL) {
		for (int i = 0; i < ASCII_LENGTH; i++) {
			if (aNode->children[i] != NULL) {
				string text = prefix + aNode->children[i]->c;
				
				if (!aNode->children[i]->keys.empty())
					cerr << text << endl;
				
				printNode(aNode->children[i], text);
			} 
		}
	}
}