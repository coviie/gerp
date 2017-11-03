/*
 *  stringProcessing.h
 *  stringProcessing Definition
 *  	   Written by : Jia Wen Goh
 *                 On : 21-04-2017
 * 
 *  stringProcessing strips bounding non-alphanumeric characters away, and
 *  returns the edited word.
 */

#ifndef STRINGPROCESSING_H_
#define STRINGPROCESSING_H_

#include <string>

// Strips bounding non-alphanumeric characters in the given string
std::string stripNonAlphaNum(std::string);

#endif