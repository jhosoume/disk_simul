/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"

struct block {
  unsigned char bytes_s[512];
};

struct sector_array {
  unsigned sector[60];
};

struct track_array {
  sector_array track[5];
};

struct fatlist{
  str file_name;
  unsigned int first_sector;
  fatlist(str name, unsigned int sector)
	  : file_name{name}, first_sector{sector} {}
};

struct fatent {
  unsigned int used;
  unsigned int eof;
  int next;
  fatent()
	  : used{0}, eof{0}, next{-1} {}
  fatent(unsigned int is_used, unsigned int is_eof, unsigned int next_cluster)
	  : used{is_used}, eof{is_eof}, next{next_cluster} {}
};

//Disk::Disk() 
    //: id{"-1"} {}

//str Disk::getId(){
    //return id;
//}
