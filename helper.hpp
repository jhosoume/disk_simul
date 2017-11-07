
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

#include "constants.hpp"

typedef std::string str; //< Defined string type

void readFile(str file_name);

void fileToArray(str file_name, struct track_array *disk);

void printOptions();

unsigned int getChoice();

str getFileName();

str listToString(std::vector <unsigned int> const &sectors);

#endif
