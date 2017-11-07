/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"
#include <iostream>

int main(void){

    std::vector <track_array> cylinders(num_cylinder);
    std::vector <fatlist> fat_files;
    std::vector <fatent> fat_sectors(num_cylinder * track_per_cylinder * sec_per_track);
    fat_files.push_back(fatlist("Nick", 0));
    fat_sectors[0].writeSector(0, 1);
    fat_sectors[1].writeSector(1);
    
    unsigned char c;
    std::cin >> c;
    block b = block();
    b.setData(0, c);
    std::cout << b.getData(0);

    cylinders.at(0).setData(0, 0, 1, c);
    std::cout << cylinders.at(0).getData(0, 0, 1);


    //run(fat_files, fat_sectors, cylinders);


    return 0;
}

