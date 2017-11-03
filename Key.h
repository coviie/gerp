/*
 *  Key.h
 *  Key Struct Definition
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  Key struct that contains the file number, line number (where the data)
 *  was stored) and the line contents (the contents of the line that the
 *  word was in)
 */

#ifndef KEY_H_
#define KEY_H_
#include <string>

struct Key {
	int		file;	// File no.
	int		line;	// Line no. of data
	std::string	data;	// Data, i.e. line contents
};

#endif