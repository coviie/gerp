/*
 *  stringProcessing.cpp
 *  stringProcessing Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  stringProcessing strips bounding non-alphanumeric characters away, and
 *  returns the edited word.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "stringProcessing.h"
using namespace std;

/* [Name]:		stripNonAlphaNum
 * [Purpose]:		Strips bounding non-alphanumeric characters away
 * [Parameters]:	1 string (word to edit)
 * [Returns]:		string (stripped word)
 */
string stripNonAlphaNum(string word) {
	int front = 0;
	int back = word.length() - 1;
	
	while (front <= back and !isalnum(word[front])) 
		front++; 
	
	while (back >= front and !isalnum(word[back])) 
		back--;
	
	return word.substr(front, back - front + 1);
}

