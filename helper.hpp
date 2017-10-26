/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
 */


#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

#include "disk.hpp"

typedef std::string str; //< Defined string type

void readFile(str file_name);

void fileToArray(str file_name, track_array * disk);
