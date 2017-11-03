/*
 *  Gerp.cpp
 *  End-User Interface
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Main; Indexes the directory given from the cmd line, then takes 
 *  input from cin and either searches (either case sensitive or insensitive)
 *  or quits. Also handles 'special' user input (i.e. entering "@i" with no
 *  inputs and quitting)
 */

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "FSTree.h"
#include "DirNode.h"
#include "TreeTraversal.h"
#include "Indexer.h"
#include "stringProcessing.h"
#include "Trie.h"
using namespace std;

//**** Function Declarations ****//
// Determines what to do with the given input
void	run(Indexer&);

//------------------------------//

//************ Main ************//
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage:  gerp directory\n"
		     << "\t    where:  directory is a valid directory\n";
		return EXIT_FAILURE;
	}
	
	Indexer fileIndex(argv[1]);
	run(fileIndex);
}

//------------------------------//

//**** Function Definitions ****//
/* [Name]:		run
 * [Purpose]:		Determines what to do with the given input
 * 			 "@q" or "@quit" - Quits the program
 * 			 "@i" or "@insensitive" - Case-insensitive search;
 * 			  (takes the next string after to search; if no 
 * 			   string is given and program is ended, search
 * 			   on "@i")
 * 			 AnyString - Case-sensitive search on the string
 * [Parameters]:	Indexer& (Indexer to search into)
 * [Returns]:		void
 */
void run (Indexer &fileIndex)
{
	string query, input;
	while (!cin.eof()) {
		query = "";
		cout << "Query? ";
		cin >> query;
		if (query != "") {
			stringstream ss(query);
			ss >> input;
			if (input == "@q" or input == "@quit") 
				break;
			
			else if (input == "@i" or input == "@insensitive") {
				if (ss.eof()) {
					cin >> input;
					fileIndex.searchInsensitive(input);
				}
				
				else {
					ss >> input;
					fileIndex.searchInsensitive(input);
				}
			}
			else 
				fileIndex.searchSensitive(input);
		}
	}
	cout << "\nGoodbye! Thank you and have a nice day.\n";
}
//------------------------------//