/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"
#include <iostream>

int main(void){

    track_array cylinders[num_cylinder]; 
    std::vector <fatlist> fat_files;
    std::vector <fatent> fat_sectors(num_cylinder * track_per_cylinder * sec_per_track);
    printOptions();
    fat_files.push_back(fatlist("Nick", 0));
    fat_sectors[0].writeSector(0, 1);
    fat_sectors[1].writeSector(1);

    sector_pos pos = getPosFromIndx(300);

    std::cout << "\n" << "Cilindro: " << pos.cylinder << "\nTrack: " << pos.track << "\nSetor: " << pos.sector << "\n\n";
    std::cout << "\n Teste " << (1 % 60) << "\n"; 

    showFAT(fat_files, fat_sectors);

    return 0;
}

