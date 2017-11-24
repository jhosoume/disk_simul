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

unsigned long choicePrompt() {
    unsigned long option;
    str numbuf;
    std::cout << "\nEscolha uma das opções: ";
    std::cin >> numbuf;
    option = std::strtoul(numbuf.c_str(), 0, 10);
    return option;
}

unsigned long getChoice() {
    unsigned long option = choicePrompt();
    while ((option < 1) || (option > 5)) {
        std::cout << "\nOpção inválida. Escolha entre uma das ações abaixo.\n";
        printOptions();
        option = choicePrompt();
    }
    return option;
}

str getFileName() {
    str file_name;
    std::cout << "\nQual o nome do arquivo a ser lido?\n";
    std::cin >> file_name;
    std::cout << "\n";
    return file_name;
}

str listToString(std::vector <unsigned int> sectors) {
    std::stringstream result;
    std::copy(sectors.begin(), sectors.end(), 
                        std::ostream_iterator<unsigned int>(result, ","));
    return result.str().substr(0, result.str().length() - 1);
}
