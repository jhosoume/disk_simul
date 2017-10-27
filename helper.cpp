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

void fileToArray(str file_name, track_array *disk) {
    char letter;
    unsigned int indx = 0;
    std::fstream fin(file_name, std::fstream::in);
    while (fin >> std::noskipws >> letter) {
            std::cout << letter; 
            indx++;
    }
}

void printOptions() {
	std::cout << "\n\n1 - Escrever Arquivo \n";
	std::cout << "2 - Ler Arquivo \n";
	std::cout << "3 - Apagar Arquivo \n";
	std::cout << "4 - Mostrar Tabela FAT \n";
	std::cout << "5 - Sair \n\n";
}


