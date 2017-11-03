/*
 *  Indexer.h
 *  Indexer Class Header and Definition
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Indexer indexes all files from the given directory, stores all the words
 *  in the Trie (wordStorage). Words are processed by stringProcessing before
 *  being stored, and the location and lineContents (e.g. /h/...: lorem ipsum)
 *  are stored with the words.
 *  Indexer then waits on gerp.cpp (main) to send in a query, and then 
 *  searches on that query (it will print the results of the search, i.e.
 *  filename, line number and contents of the line it's found in).
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "TreeTraversal.h"
#include "stringProcessing.h"
#include "Trie.h"

class Indexer {
public:
	/******************************** 
	 * Constructors and Destructors *
	 ********************************/
	// Intializes the indexer from the given directory
	Indexer(std::string);
	
	// Destructor that destroys heap-allocated data
	~Indexer();
	
	/******************************** 
	 *        Search Functions      *
	 ********************************/
	// Case-sensitive search
	void	searchSensitive(std::string);
	
	// Case-insensitive search
	void	searchInsensitive(std::string);
	
private:
	/******************************** 
	 *       Indexer Variables      *
	 ********************************/
	// TreeTraversal object that traverses directories from given root
	TreeTraversal *directory;
	
	// Trie that will store all the words
	Trie wordStorage;
	
	// Vector that stores all the filenames from TreeTraversal obj
	std::vector<std::string> fileList;
	
	/******************************** 
	 *        Helper Functions      *
	 ********************************/
	// Initiates the word storage process
	void storeWords();
	
	// Opens the given file (and note what file # it is)
	void openFile(std::string, int);
	
	// Parses the line into individual words, processes them and stores
	// them
	void read(std::string, Key);
	
	// Prints the results of the search
	bool printResults(std::string, std::vector<Key>);
};

#endif