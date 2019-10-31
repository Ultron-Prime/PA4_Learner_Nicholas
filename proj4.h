
#ifndef PROJ4_H
#define PROJ4_H

#include <iostream>

using namespace std;

#define MAX_CHAR_ARRAY_SIZE 256
#define NUM_OF_SENSORS 3
#define NUM_OF_CARS 5

// Required functions that deal with char arrays
size_t myStringLength(const char * str);
int myStringCompare(const char * str1, const char * str2);
char * myStringCopy(char * destination, const char * source);
char * myStringCat(char * destination, const char * source);

// Added error function
void Error();

#endif
