/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

// Simple definition of types
//typedef MyTree::Node< std::string> BNode; //< Class that defines the base definition of a Binary Tree
//typedef MyTree::Side Side; //< Enumerations to identify sides of a Binary Tree ramification
typedef std::string str; //< Defined string type

typedef struct block {
    unsigned char bytes_s[512];
} block;
typedef struct sector_array {
    unsigned sector[60];
} sector_array;
typedef struct track_array {
    sector_array track[5];
} track_array;
typedef struct fatlist_s{
    char file_name[100];
    unsigned int first_sector;
} fatlist;
typedef struct fatent_s {
    unsigned int used;
    unsigned int eof;
    unsigned int next;    
} fatent;

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
