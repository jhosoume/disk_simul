
#ifndef HELPER
#define HELPER

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <algorithm>

#include "constants.hpp"

typedef std::string str; //< Defined string type

void readFile(str const &file_name);

void fileToArray(str const &file_name, struct track_array *disk);

void printOptions();

unsigned long getChoice();

str getFileName();

str listToString(std::vector <unsigned int> const &sectors);

unsigned int fileSize(str const &file_name);

#endif
