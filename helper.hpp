
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

#include "constants.hpp"

typedef std::string str; //< Defined string type

void readFile(str file_name);

void fileToArray(str file_name, struct track_array *disk);

#endif
