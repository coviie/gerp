/*
 *  TreeTraversal.cpp
 *  TreeTraversal Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Tree Traversal class that traverses the directory (from the given 
 *  directory), storing filenames into a vector string as it does.
 */

#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"
#include "TreeTraversal.h"
using namespace std;

/*******************************
 *  Constructors & Destructors *
 *******************************/
/* [Name]:		TreeTraversal
 * [Purpose]:		Constructor; Initializes an FSTree, storing the 
 * 			filenames from the given directory
 * [Parameters]:	1 string (directory name to look into)
 * [Returns]:		-
 */
TreeTraversal::TreeTraversal(string directoryName)
{
	directory = new FSTree(directoryName);
	
	root 	 = directory->getRoot();
	rootName = root->getName();
	
	crawl(root, rootName);
}

/* [Name]:		~TreeTraversal
 * [Purpose]:		Destructor; Deletes the heap-allocated data 
 * 			(FSTree pointer).
 * [Parameters]:	-
 * [Returns]:		-
 */
TreeTraversal::~TreeTraversal()
{
	delete directory;
}

/*******************************
 *  Directory-Search Functions *
 *******************************/
/* [Name]:		crawl
 * [Purpose]:		Crawls through the given directory (DirNode*) and 
 * 			stores all the files (and their location) into the 
 * 			given string vector.
 * 
 * 			(Steps):
 * 				1. Process files
 * 				2. Recursively enter subdirectories
 * 			note: tail end recursion, i.e. process files before 
			recursively entering subdirectories so it only 
			creates stack-frame at the end of the function
			for the recursion call (memory-efficient since you 
			don't have pending files to read/steps to do)
			
 * [Parameters]:	1 DirNode* (given directory to process), 1 string 
 * 			rootName (directory name to be added)
 * [Returns]:		void
 */
void TreeTraversal::crawl(DirNode *directory, string rootName)
{
	if (directory->isEmpty())
		return;
	
	// Directory with files
	if (directory->hasFiles())
		processFiles(directory, rootName);
	
	// Enter subdirectories
	for (int i = 0; i < directory->numSubDirs(); i++) {
		DirNode *subdir = directory->getSubDir(i);
		string prefix = rootName + "/" + subdir->getName();
		crawl(subdir, prefix);
	}
}

/* [Name]:		processFiles
 * [Purpose]:		Stores the filenames into the string vector
 * [Parameters]:	1 DirNode* (given directory to process), 1 string 
 * 			rootName (directory name to be added)
 * [Returns]:		void
 */
void TreeTraversal::processFiles(DirNode *directory, string rootName) 
{
	for (int i = 0; i < directory->numFiles(); i++) {
		string filename = directory->getFile(i);
		directoryList.push_back(rootName + "/" + filename);
	}
}

/* [Name]:		print
 * [Purpose]:		Prints the filenames stored in the given string vector
 * [Parameters]:	-
 * [Returns]:		void
 */
void TreeTraversal::print() 
{
	size_t listLength = directoryList.size();
	for (size_t i = 0; i < listLength; i++)
		cout << directoryList[i] << endl;
}

/* [Name]:		getDirectoryList
 * [Purpose]:		Returns the list of directories
 * [Parameters]:	-
 * [Returns]:		1 vector<string> (list of directories)
 */
vector<string> TreeTraversal::getDirectoryList()
{
	return directoryList;
}

