/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "helper.hpp"

void readFile(str file_name) {
    char letter;
    std::fstream fin(file_name, std::fstream::in);
    while (fin >> std::noskipws >> letter) {
            std::cout << letter; 
    }
}

void fileToArray(str file_name, track_array * disk) {
}

