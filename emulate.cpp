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
    
    //unsigned char c;
    //std::cin >> c;
    //block b = block();
    //b.setData(0, c);
    //std::cout << b.getData(0);

    //cylinders.at(0).setData(0, 0, 1, c);
    //std::cout << cylinders.at(0).getData(0, 0, 1);
    //test(cylinders);


    run(fat_files, fat_sectors, cylinders);
    //std::cout << "\n Checking " << "sec at 0 is" << fat_sectors.at(0).used;


    return 0;
}

