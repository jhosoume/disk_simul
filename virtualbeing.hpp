/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 13/0118184
 *  MATÉRIA: Estruturas de Dados
 *  SEMESTRE: Segundo Semestre de 2015
 *  CURSO: Física
*/

#include <ctime>
#include <cstdlib>
#include <vector>
#include "btree.hpp"

// Simple definition of types
typedef MyTree::Node< std::string> BNode; //< Class that defines the base definition of a Binary Tree
typedef MyTree::Side Side; //< Enumerations to identify sides of a Binary Tree ramification
typedef std::string str; //< Defined string type

/**
 * \class Being
 * \brief A virtual being with random characteristics. Can reproduce and constitutes a population.
 * Defines a virtual Being from several established genes that corresponds to
 * specific phenotypes. If the being
 * was not generated from a custom reproduction of the species, his carachteristics
 * are selected at random. His identification consists of a identification number and
 * parents numbering.
 */
class Being {
public:

	/**
     * Being constructor to just defines its size to the compilation process.
     * @see Being(str value)
     * @see Being(str value, str p1, str p2)
     */
    Being();

	/**
     * Creates a Being with random characteristics.
     * Using this method, the Being is created from scratch. Random characteristics
     * are selected (BTree level 4)), but the main structure (BTree levels 0, 1, 2 and 3)
     * is maintained. To generate a Being that way, no parents are needed.
     * @param value the individual identification.
     * @return a being generated from scratch
     */
    Being(str);

	/**
     * Creates a Being with inherited characteristics.
     * Using this method, the Being is with the basic structure, meaning arms, legs, 
     * eyes etc, nonetheless the characteristics are inherited from the parents.
     * The phenotype is defined from genes dominance relation.
     * @param value the individual identification.
     * @param p1 indicates one of the parents
     * @param p2 indicates the second parent
     * @return a being generated from scratch
     */
    Being(str, str, str);

    /**
     * Function that describes the being.
     * This function uses BTree travel to reach genes from the Being and 
     * determins the dominance relation to output the Being phenotype.
     * Does not have any return, but prints the characteristics in the terminal.
     */
    void describe();

    /**
     * Generate a new Being, stipulating the first parent as the Being that calls this function, the other one is defined from the parameter.
     * @param value defines the id of the child
     * @param parent2 defines the second parent of the generated being
     * @return returns a new Being
     */
    Being * reproduce(str, Being *);

    /*
     * Auxiliary function to just provide the id from the current object.
     * Extracts the id from the object from whom this methods is called
     * @return return a string corresponding to the Being id.
     */
    str getId();

private:
    BNode *structure; ///< Being basic structure as a Binary Tree 
    str id; ///< String that stores the Being identification
    str parent_1; ///< String that stores the identification of one of the parents
    str parent_2; ///< String that stores the identification of the other parent

    /**
     * Defines both genes for the eye color.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineEyeColor();
    void singleEyeColor(Side);

    /**
     * Defines both genes for the eye format.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineEyeFormat();
    void singleEyeFormat(Side);

    /**
     * Defines both genes for the hair color.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineHairColor();
    void singleHairColor(Side);

    /**
     * Defines both genes for the hair type.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineHairType();
    void singleHairType(Side);

    /**
     * Defines both genes for the arms.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineArms();
    void singleArm(Side);

    /**
     * Defines both genes for the legs.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineLegs();
    void singleLeg(Side);

    /**
     * Defines both genes for the neck.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineNeck();
    void singleNeck(Side);

    /**
     * Defines both genes for the fur.
     * Used to pick a rangom gene when the being is created randomly. 
     * Does not return, but changes the Being that called the function.
     */
    void defineFur();
    void singleFur(Side);

    /**
     * Compares the genes of the Beign.
     * @param atrib Genes pair to be compared.
     * @return the string of the gene  that has the dominance
     */
    str dominance(str);

    /**
     * Auxiliary method to set the being genes, after reproduction.
     * Needs the parents to generate the new being and the id of the new being
     * Does not returns but alters the being that called this method
     * @param father receives one being
     * @param mother receives the other being. Cannot be equalt to father
     */
    void setAtt(Being *,Being *, str att);
};
