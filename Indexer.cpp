/*
 *  Indexer.cpp
 *  Indexer Implementation
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

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "TreeTraversal.h"
#include "Indexer.h"
#include "stringProcessing.h"
#include "Trie.h"
#include "Key.h"
using namespace std;

/*******************************
 *  Constructors & Destructors *
 *******************************/
/* [Name]:		Indexer
 * [Purpose]:		Constructor; Initializes the indexer from the 
 * 			given directory, and processes all words from 
 * 			the files indexed
 * [Parameters]:	1 string (directory that should be indexed)
 * [Returns]:		-
 */
Indexer::Indexer(string directoryName)
{
	directory = new TreeTraversal(directoryName);
	fileList = directory->getDirectoryList();
	storeWords();
}

/* [Name]:		~Indexer
 * [Purpose]:		Destructor; Destroys the heap-allocated data
 * 			(TreeTraversal ptr)
 * [Parameters]:	-
 * [Returns]:		-
 */
Indexer::~Indexer()
{
	delete directory;
}

/*******************************
 *    File Reading Functions   *
 *******************************/
/* [Name]:		storeWords
 * [Purpose]:		Initiates the word storage process by opening all
 * 			the files
 * [Parameters]:	-
 * [Returns]:		void
 */
void Indexer::storeWords()
{
	for (size_t fileNum = 0; fileNum < fileList.size(); fileNum++)
		openFile(fileList[fileNum], (int)fileNum);
	
}

/* [Name]:		openFile
 * [Purpose]:		Opens the given file, gets each line, and then 
 * 			parses each line (i.e. processes each word in
 * 			the line, and stores it). Also stores/processes
 * 			the 'Key' for each word (i.e. its file #, line it's
 * 			found in, and the contents of the line it's found in)
 * [Parameters]:	1 string (filename), 1 int (the n-th file from
 * 			the fileList vector)
 * [Returns]:		void
 */
void Indexer::openFile(string filename, int fileNum)
{
	ifstream inf;
	inf.open(filename);
	if (!inf.is_open()) 
		return;
	
	int lineNumber = 0;
	string lineContents;
	
	while (getline(inf, lineContents)) {
		lineNumber++;
		
		Key location;
		location.line = lineNumber;
		location.file = fileNum;
		location.data = lineContents;
		
		read(lineContents, location);
	}
	
	inf.close();
}

/* [Name]:		read
 * [Purpose]:		Takes the line that from openFile, processes each
 * 			word in the line, and stores them (along with the
 * 			location info)
 * [Parameters]:	1 string (lineContents to be parsed), 1 Key (location
 * 			where it's found in)
 * [Returns]:		void
 */
void Indexer::read(string lineContents, Key location)
{
	if (lineContents != "") {
		string word;
		stringstream line(lineContents);

		while (!line.eof()) {
			line >> word;
			word = stripNonAlphaNum(word);
			if (word != "")
				wordStorage.addWord(word, location);
		}
	}
}

/*******************************
 *       Search Functions      *
 *******************************/
/* [Name]:		searchSensitive
 * [Purpose]:		Does a case-sensitive search based on the given
 * 			query, and prints the results
 * [Parameters]:	1 string (query)
 * [Returns]:		void
 */
void Indexer::searchSensitive(string query)
{
	vector<Key> location;
	query = stripNonAlphaNum(query);
	location = wordStorage.searchSensitive(query);
	
	if (!printResults(query, location))
		cout << " Try with @insensitive or @i.\n";
}

/* [Name]:		searchInsensitive
 * [Purpose]:		Does a case-insensitive search based on the given
 * 			query, and prints the results
 * [Parameters]:	1 string (query)
 * [Returns]:		void
 */
void Indexer::searchInsensitive(string query)
{
	vector<Key> location;
	query = stripNonAlphaNum(query);
	location = wordStorage.searchInsensitive(query);
	
	if (!printResults(query, location))
		cout << endl;
}

/*******************************
 *       Print Functions       *
 *******************************/
/* [Name]:		printResults
 * [Purpose]:		Prints the results of the search (i.e. where it's
 * 			found) in the format:
 * 			  /rootname/filename:line: data
 * [Parameters]:	1 string (query), 1 vector<Key> (every instance where
 * 			the word is found)
 * [Returns]:		bool (true if the word exists, and location is 
 * 			printed, false if otherwise)
 */
bool Indexer::printResults(string query, vector<Key> location)
{
	if (!location.empty()) {
		for (size_t i = 0; i < location.size(); i++)  {
			cout << fileList[location[i].file] << ":" 
			     << location[i].line << ": " 
			     << location[i].data << endl;
		}
		return true;
	}
	
	else {
		cout << query << " Not Found.";
		return false;
	}
}