/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"

void showFAT(std::vector <fatlist> files, std::vector <fatent> sectors) {
	std::cout << std::left << std::setw(20) << "Nome: "; 
	std::cout << std::left << std::setw(20) << "Tamanho em Disco: ";
	std::cout << std::left << std::setw(20) << "Localização:\n";
    for (fatlist file : files) {
        file_sectors secs = fileSectors(file.first_sector, sectors); 
	    std::cout << std::left << std::setw(20) << file.file_name; 
        std::cout << std::left << std::setw(20) << secs.size; 
        std::cout << std::left << std::setw(20) 
            << listToString(secs.sectors) << std::endl; 
    }
}

file_sectors fileSectors(unsigned int first_sector, 
                            std::vector <fatent> sectors) {
    file_sectors fsecs = file_sectors(1, {first_sector});
    fatent current_sec = sectors.at(first_sector);
    while (current_sec.eof != 1) {
        fsecs.size++;
        fsecs.sectors.push_back(current_sec.next);
        current_sec = sectors.at(current_sec.next);
    }
    fsecs.size *= sector_size;
    return fsecs;
}

void writeFile(str file_name, std::vector <fatlist> file_list, 
                                       std::vector <fatent> fat) {
}

size_t nextFreeSector(unsigned int start, std::vector <fatent> sectors) {
    size_t indx = start;
    fatent sec = sectors[indx];
    while (indx < sectors.size() && sec.used != 0) {
        indx++;
        sec = sectors[indx];
    }
    return indx; 
}



Disk::Disk() 
    : id{"-1"} {}

str Disk::getId(){
    return id;
}
