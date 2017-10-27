/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"

void get_sectors(unsigned int beg, unsigned int size) {
}

void showFAT(std::vector <fatlist> files, std::vector <fatent> sectors) {
	std::cout << std::left << std::setw(20) << "Nome: "; 
	std::cout << std::left << std::setw(20) << "Tamanho em Disco: ";
	std::cout << std::left << std::setw(20) << "Localização:\n";
    for (fatlist file : files) {
        //file_sectors secs = fileSectors(file.first_sector, sectors); 
	    std::cout << std::left << std::setw(20) << file.file_name; 
		//std::cout << std::left << std::setw(20) << secs.size; 
		//std::cout << std::left << std::setw(20) << secs.sectors 
                                                    //<< std::endl; 
    }
	//std::cout << std::setw(20) << std::setw(20) << std::setw(20)
}

file_sectors fileSectors(unsigned int first_sector, std::vector <fatent> sectors) {
    //TODO Should deal with an empty sectors vector
    file_sectors fsecs = file_sectors();
    fsecs.sectors.push_back(first_sector);
    unsigned int current_sec = first_sector;
    unsigned int eof = sectors.at(first_sector).eof;
    while (eof != 1) {
        fsecs.size++;
        current_sec = sectors.at(current_sec).next;
        fsecs.sectors.push_back(current_sec);
    }
    fsecs.size *= sector_size;
    return fsecs;
}


Disk::Disk() 
    : id{"-1"} {}

str Disk::getId(){
    return id;
}
