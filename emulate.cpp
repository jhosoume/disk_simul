/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"
#include <iostream>

int main(void){

    track_array cylinder[num_cylinder]; 
    std::vector <fatlist> fat_files;
    std::vector <fatent> fat_sectors;
    printOptions();
    fat_files.push_back(fatlist("Nick", 0));

    showFAT(fat_files, fat_sectors);

    return 0;
}

