/*
 *  TreeTraversal.h
 *  TreeTraversal Class Header and Definition
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Tree Traversal class that traverses the directory (from the given 
 *  directory), storing filenames into a vector string as it does.
 */

#ifndef TREETRAVERSAL_H_
#define TREETRAVERSAL_H_

#include <string>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"

class TreeTraversal {
public:
	/******************************** 
	 * Constructors and Destructors *
	 ********************************/
	// Initializes a TreeTraversal that will traverse the given directory
	TreeTraversal(std::string);
	
	// Destructor that destroys heap-allocated data
	~TreeTraversal();
	
	/******************************** 
	 *        Other Functions       *
	 ********************************/
	// Prints all the stored filenames
	void print();
	
	// Returns the list of directories
	std::vector<std::string> getDirectoryList();
	
private:
	/******************************** 
	 *   TreeTraversal Variables    *
	 ********************************/
	// FSTree object that will be crawling through the directories
	FSTree	*directory;
	
	// Directory root
	DirNode	*root;
	
	// A list of directories
	std::vector<std::string> directoryList;
	
	// The string that is the rootname of the directory
	// 	i.e. /h/...
	std::string rootName;
	
	/******************************** 
	 *   TreeTraversal Functions    *
	 ********************************/
	// Crawls through the given directory
	void crawl(DirNode*, std::string);
	
	// Stores the filenames into the string vector
	void processFiles(DirNode*, std::string);
};

#endif