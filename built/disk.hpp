/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#ifndef DISK
#define DISK

#include "helper.hpp"

/* Simple definition of types that store information */
typedef struct block {
    unsigned char bytes_s[sector_size];
    void setData(unsigned int byte, unsigned char data);
    unsigned char getData(unsigned int byte);
} block;

typedef struct sector_array {
    block sector[sec_per_track];
    void setData(unsigned int block, unsigned int byte, unsigned char data);
    unsigned char getData(unsigned int block, unsigned int byte);
} sector_array;

typedef struct track_array {
    sector_array track[track_per_cylinder];
    void setData(unsigned int track, unsigned int block, unsigned int byte, unsigned char data);
    unsigned char getData(unsigned int track, unsigned int block, unsigned int byte);
} track_array;
 /*_________________________________________________________________________*/

/* List of files saved */
typedef struct fatlist {
    str file_name;
    unsigned int first_sector;
    fatlist(str name, unsigned int sector) 
        : file_name{name}, first_sector{sector} {}
    fatlist()
        : file_name{"not found"}, first_sector{0} {}
} fatlist;

 /*_________________________________________________________________________*/

 /* Stores the cylinder, track and sector position of an indx(defined sector)*/
typedef struct sector_pos {
    unsigned int cylinder;
    unsigned int track;
    unsigned int sector;
    sector_pos()
        : cylinder{0}, track{0}, sector{0} {}
    sector_pos(unsigned int cyl, unsigned int trck, unsigned int sec)
        : cylinder{cyl}, track{trck}, sector{sec} {}
} sector_position;
 /*_________________________________________________________________________*/

/* Stores the state of each sector */
typedef struct fatent {
    unsigned int used;
    unsigned int eof;
    int next;    
    fatent()
        : used{0}, eof{0}, next{-1} {}
    fatent(unsigned int is_used, unsigned int is_eof, int next_cluster)
        : used{is_used}, eof{is_eof}, next{next_cluster} {}
    void mark();
    void writeSector(unsigned int next);
    void writeSector(unsigned int eof, int next);
    void print();
    void free();
} fatent;
 /*_________________________________________________________________________*/

/* Total size and all sectors that belong to a certain file */
typedef struct file_sectors {
    unsigned long int size;
    std::vector <unsigned int> sectors;
    file_sectors()
        : size{0}, sectors{std::vector <unsigned int>()} {}
    file_sectors(unsigned long int size, 
                        std::vector <unsigned int> secs)
        : size{size}, sectors{secs} {}
} file_sectors;
 /*_________________________________________________________________________*/


/* Function that presents the files stored. Show its sectors and size */
void showFAT(std::vector <fatlist> const &files, std::vector <fatent> const &sectors);

/* Traverse the Fat Entity to obtain the location of the portions 
 * of the file. The result is a structure (file_sectors) with the 
 * total size in disk besides all the occupied sectos in a vector.  */
file_sectors fileSectors(unsigned int first_sector, 
                            std::vector <fatent> sectors);

/* Directory is based in the folder that the program is being run. 
 * Reads a file entry and stores in the virtual HD. The total time to write th 
 * file is written in the end. */
void writeFile(str const &file_name, std::vector <fatlist> &file_list,
                        std::vector <fatent> &fat, std::vector <track_array> &cylinders);

/* Writes the information stored in the virtual HD to a file in the previous 
 * directory inside folder named read. Get all bytes bounded to a filename. */
void readFile(str filename, std::vector <fatlist> &file_list,
             std::vector <fatent> &fat, std::vector <track_array> &cylinders);

/* Remove a file from the FAT list. Data cannot be retrieved. */
void deleteFile(str filename, std::vector <fatlist> &file_list,
             std::vector <fatent> &fat, std::vector <track_array> &cylinders);

/* To prevent data from previous files stay in the not fully filled cluster,
 * write null char when closing. */
void fillBlock(unsigned int num_sector, unsigned int byte, std::vector <track_array> &cylinders);

/* Closes the sectors that belongs to a given cluster*/
void closeCluster(unsigned int num_sector, std::vector <fatent> &sectors,
                                          unsigned int byte, std::vector <track_array> &cylinders);

size_t freeCluster(std::vector <fatent> const &sectors);

sector_pos begOfCluster(sector_pos pos);

sector_pos begOfCluster(unsigned int indx);

size_t nextFreeCluster(sector_pos pos, std::vector <fatent> const &sectors);

size_t nextFreeSector(sector_pos pos, std::vector <fatent> const &sectors);

sector_pos getPosFromIndx(unsigned int indx);

unsigned int getIndxFromPos(sector_pos pos);

fatlist findFat(str const &name, std::vector <fatlist> &fat_list);

bool inFat(str const &name, std::vector <fatlist> &fat_list);

void eraseFat(str const &name, std::vector <fatlist> &fat_list);

void run(std::vector <fatlist> &file_list,
                   std::vector <fatent> &fat, std::vector <track_array> &cyls);

unsigned int fileSizeDisk (str const &name, std::vector <fatlist> &files,
                                                  std::vector <fatent> const &sectors);

unsigned int numSeeks(std::vector <unsigned int> const &sectors);

double measureTime(file_sectors const &sectors);


class Disk {
public:
    Disk();
    str getId();

private:
    str id;
};

#endif
