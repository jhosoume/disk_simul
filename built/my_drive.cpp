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
    
    run(fat_files, fat_sectors, cylinders);

    return 0;
}

