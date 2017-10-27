/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#ifndef DISK
#define DISK

#include "helper.hpp"

// Simple definition of types

typedef struct block {
    unsigned char bytes_s[512];
} block;

typedef struct sector_array {
    unsigned sector[60];
} sector_array;

typedef struct track_array {
    sector_array track[5];
} track_array;

typedef struct fatlist{
    str file_name;
    unsigned int first_sector;
    fatlist(str name, unsigned int sector) 
        : file_name{name}, first_sector{sector} {}
} fatlist;

typedef struct fatent {
    unsigned int used;
    unsigned int eof;
    int next;    
    fatent()
        : used{0}, eof{0}, next{-1} {}
    fatent(unsigned int is_used, unsigned int is_eof, unsigned int next_cluster)
        : used{is_used}, eof{is_eof}, next{next_cluster} {}
} fatent;

typedef struct file_sectors {
    unsigned long int size;
    std::vector <unsigned int> sectors;
    file_sectors()
        : size{0}, sectors{std::vector <unsigned int>()} {}
} file_sectors;

void get_sectors(unsigned int beg, unsigned int size); 

void showFAT(std::vector <fatlist> files, std::vector <fatent> sectors);

file_sectors fileSectors(unsigned int first_sector, 
                            std::vector <fatent> sectors);

/**
 * \class Being
 * \brief A virtual being with random characteristics. Can reproduce and constitutes a population.
 * Defines a virtual Being from several established genes that corresponds to
 * specific phenotypes. If the being
 * was not generated from a custom reproduction of the species, his carachteristics
 * are selected at random. His identification consists of a identification number and
 * parents numbering.
 */
class Disk {
public:

	/**
     * Being constructor to just defines its size to the compilation process.
     * @see Being(str value)
     * @see Being(str value, str p1, str p2)
     */
    Disk();

    /*
     * Auxiliary function to just provide the id from the current object.
     * Extracts the id from the object from whom this methods is called
     * @return return a string corresponding to the Being id.
     */
    str getId();

private:
    str id;

};

#endif
