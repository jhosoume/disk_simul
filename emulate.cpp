/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"
using namespace std;

const unsigned int numCylinder = 4;
const unsigned int cluster_size = 4;
const unsigned int seek_time = 4;
const unsigned int latency = 6;
const unsigned int transf = 12; 


int main(void){

    track_array cylinder[numCylinder]; 
    vector <fatlist> fat_files;
    vector <fatent> fat_sectors;
    
    readFile("sample.txt");

    return 0;
}
