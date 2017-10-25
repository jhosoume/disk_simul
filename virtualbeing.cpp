/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 13/0118184
 *  MATÉRIA: Estruturas de Dados
 *  SEMESTRE: Segundo Semestre de 2015
 *  CURSO: Física
*/

#include "virtualbeing.hpp"

Being::Being() 
    : structure{nullptr}, id{"-1"}, parent_1{"0"}, parent_2{"0"} 
{
    // This implamentation of the constructor is here to provide
    // the space needed for this representation for compilation.

    // Tried to encapsulate the following structure within a function withou success
    // Compiler error (x86)
    structure = new BNode(id);       

    // Add being format according to the specified project
    // So the head is specified after the id node
    // All basic structures of the being are defined here
    structure->addLeft("cabeça", id);
    structure->addRight("corpo", id);

    structure->addLeft("olhos", "cabeça");
    structure->addRight("cabelos", "cabeça");

    structure->addLeft("Cor", "olhos");
    structure->addRight("formato", "olhos");

    structure->addLeft("cor", "cabelos");
    structure->addRight("tipo", "cabelos");

    structure->addLeft("membros", "corpo");
    structure->addRight("tronco", "corpo");

    structure->addLeft("braços", "membros");
    structure->addRight("pernas", "membros");

    structure->addLeft("pescoço", "tronco");
    structure->addRight("pelos", "tronco");

    // Uses random numbers to define each characteristic 
    // from the characteristic table
    defineEyeColor();
    defineEyeFormat();
    defineHairColor();
    defineHairType();
	defineArms();
	defineLegs();
    defineNeck();
    defineFur();
}

// Same constructor as before but the id is defined
Being::Being(str value) 
    : structure{nullptr}, id{value}, parent_1{"0"}, parent_2{"0"} 
{
    // Tried to encapsulate the following structure within a function withou success
    // Compiler error (x86)
    structure = new BNode(id);       

    structure->addLeft("cabeça", id);
    structure->addRight("corpo", id);

    structure->addLeft("olhos", "cabeça");
    structure->addRight("cabelos", "cabeça");

    structure->addLeft("Cor", "olhos");
    structure->addRight("formato", "olhos");

    structure->addLeft("cor", "cabelos");
    structure->addRight("tipo", "cabelos");

    structure->addLeft("membros", "corpo");
    structure->addRight("tronco", "corpo");

    structure->addLeft("braços", "membros");
    structure->addRight("pernas", "membros");

    structure->addLeft("pescoço", "tronco");
    structure->addRight("pelos", "tronco");

    defineEyeColor();
    defineEyeFormat();
    defineHairColor();
    defineHairType();
	defineArms();
	defineLegs();
    defineNeck();
    defineFur();
    
    //Following methods are used to verify correctness
    //structure->BFS();
    //describe();
}


Being::Being(str value, str p1, str p2)
    : structure{nullptr}, id{value}, parent_1{p1}, parent_2{p2}
    // defines not only the id, but also his parents
 {
    structure = new BNode(id);       

    structure->addLeft("cabeça", id);
    structure->addRight("corpo", id);

    structure->addLeft("olhos", "cabeça");
    structure->addRight("cabelos", "cabeça");

    structure->addLeft("Cor", "olhos");
    structure->addRight("formato", "olhos");

    structure->addLeft("cor", "cabelos");
    structure->addRight("tipo", "cabelos");

    structure->addLeft("membros", "corpo");
    structure->addRight("tronco", "corpo");

    structure->addLeft("braços", "membros");
    structure->addRight("pernas", "membros");

    structure->addLeft("pescoço", "tronco");
    structure->addRight("pelos", "tronco");

    //structure->BFS();
 }

str Being::getId(){
    return id;
}

Being *Being::reproduce(str value, Being *parent2) {
    // Since this method is called from an Being object,
    // one of the parents is the owner of this method, the
    // other is provided in the parameter.
    Being *child = new Being(value, id, parent2->getId());
    // Creates the new Being and grab randomly the genes from the parents
    std::vector<str> att_list = {"Cor", "formato", "cor", "tipo", "braços", "pernas", "pescoço", "pelos"};
    // Loop to establish all the new Being genes from his parents
    for (auto attb : att_list) 
        child->setAtt(this, parent2, attb);
    // following functions are to acertain the correctness of the reproduction
    //child->structure->BFS();
    //child->describe();
    return child;
}
void Being::setAtt(Being *father, Being *mother, str att) {
    // Creates a list of the parents genes
    std::vector<str> fatherGenes(2);
    std::vector<str> motherGenes(2);
    fatherGenes[0] = father->structure->leftInfo(att);
    fatherGenes[1] = father->structure->rightInfo(att);
    motherGenes[0] = mother->structure->leftInfo(att);
    motherGenes[1] = mother->structure->rightInfo(att);
    // Pick randomly the gene to be inherited
    // One gene must come from the father and one from the mother
    int parent = (std::rand() % 2); // First select the parent to pass the gene
    if (parent == 0) {
        int gene = (std::rand() % 2);
        structure->addLeft(fatherGenes[gene], att);
        gene = (std::rand() % 2);
        structure->addRight(motherGenes[gene], att);
    } else if (parent == 1) {
        int gene = (std::rand() % 2);
        structure->addLeft(motherGenes[gene], att);
        gene = (std::rand() % 2);
        structure->addRight(fatherGenes[gene], att);
    } else {
        std::cout << "Problem with random number for definition of heredity";
    }
}

void  Being::singleEyeColor(Side side) {
    int gene = (std::rand() % 4); // Max number must be 3
    std::string atrib;
    if (gene == 0) 
        atrib = "azul";
    else if (gene == 1)
        atrib = "castanho";
    else if (gene == 2)
        atrib = "preto";
    else if (gene == 3)
        atrib = "verde";      
    else
        std::cout << "Please, check eye color, number is " << gene << "\n";

    if (side == Side::left)
        structure->addLeft(atrib, "Cor");
    else if (side == Side::right)
        structure->addRight(atrib, "Cor");
    else
        std::cout << "Side to add eye color is wrong\n";
}

void Being::defineEyeColor() {
    singleEyeColor(Side::left);
    singleEyeColor(Side::right);
}

void  Being::singleEyeFormat(Side side) {
    int gene = (std::rand() % 2); // Max number must be 1
    std::string atrib;
    if (gene == 0) 
        atrib = "redondo";
    else if (gene == 1)
        atrib = "vertical";
    else
        std::cout << "Please, check eye format, number is " << gene << "\n";

    if (side == Side::left)
        structure->addLeft(atrib, "formato");
    else if (side == Side::right)
        structure->addRight(atrib, "formato");
    else
        std::cout << "Side to add eye format is wrong\n";
}

void Being::defineEyeFormat() {
    singleEyeFormat(Side::left);
    singleEyeFormat(Side::right);
}

void Being::singleHairColor(Side side) {
    int gene = (std::rand() % 4); // Max number must be 3
    std::string atrib;
    if (gene == 0) 
        atrib = "castanho";
    else if (gene == 1)
        atrib = "loiro";
    else if (gene == 2)
        atrib = "preto";
    else if (gene == 3)
        atrib = "ruivo";
    else
        std::cout << "Please, check hair color, number is " << gene << "\n";

    if (side == Side::left)
        structure->addLeft(atrib, "cor");
    else if (side == Side::right)
        structure->addRight(atrib, "cor");
    else
        std::cout << "Side to add hair color is wrong\n";
}

void Being::defineHairColor() {
    singleHairColor(Side::left);
    singleHairColor(Side::right);
}

void Being::singleHairType(Side side) {
    int gene = (std::rand() % 4); // Max number must be 3
    std::string atrib;
    if (gene == 0) 
        atrib = "encaracolado";
    else if (gene == 1)
        atrib = "liso";
    else if (gene == 2)
        atrib = "velcro";
    else if (gene == 3)
        atrib = "zero";
    else
        std::cout << "Please, check hair type, number is " << gene << "\n";

    if (side == Side::left)
        structure->addLeft(atrib, "tipo");
    else if (side == Side::right)
        structure->addRight(atrib, "tipo");
    else
        std::cout << "Side to add hair type is wrong\n";
}

void Being::defineHairType() {
    singleHairType(Side::left);
    singleHairType(Side::right);
}

void Being::singleArm(Side side) {
	int gene = (std::rand() % 3); // Max number must be 2
	std::string atrib;
	if (gene == 0) 
		atrib = "curtos";
	else if (gene == 1)
		atrib = "médios";
	else if (gene == 2)
		atrib = "longos";
	else
		std::cout << "Please, check arm, number is " << gene << "\n";

	if (side == Side::left)
		structure->addLeft(atrib, "braços");
	else if (side == Side::right)
		structure->addRight(atrib, "braços");
	else
		std::cout << "Side to add arm is wrong\n";
}

void Being::defineArms() {
	singleArm(Side::left);
	singleArm(Side::right);
}

void Being::singleLeg(Side side) {
	int gene = (std::rand() % 3); // Max number must be 2
	std::string atrib;
	if (gene == 0) 
		atrib = "curtas";
	else if (gene == 1)
		atrib = "longas";
	else if (gene == 2)
		atrib = "médias";
	else
		std::cout << "Please, check leg, number is " << gene << "\n";

	if (side == Side::left)
		structure->addLeft(atrib, "pernas");
	else if (side == Side::right)
		structure->addRight(atrib, "pernas");
	else
		std::cout << "Side to add leg is wrong\n";
}

void Being::defineLegs() {
	singleLeg(Side::left);
	singleLeg(Side::right);
}

void Being::singleNeck(Side side) {
	int gene = (std::rand() % 3); // Max number must be 2
	std::string atrib;
	if (gene == 0) 
		atrib = "curto";
	else if (gene == 1)
		atrib = "longo";
	else if (gene == 2)
		atrib = "médio";
	else
		std::cout << "Please, check neck, number is " << gene << "\n";

	if (side == Side::left)
		structure->addLeft(atrib, "pescoço");
	else if (side == Side::right)
		structure->addRight(atrib, "pescoço");
	else
		std::cout << "Side to add neck is wrong\n";
}

void Being::defineNeck() {
	singleNeck(Side::left);
	singleNeck(Side::right);
}

void Being::singleFur(Side side) {
	int gene = (std::rand() % 2); // Max number must be 2
	std::string atrib;
	if (gene == 0) 
		atrib = "peludo";
	else if (gene == 1)
		atrib = "liso";
	else
		std::cout << "Please, check Fur, number is " << gene << "\n";

	if (side == Side::left)
		structure->addLeft(atrib, "pelos");
	else if (side == Side::right)
		structure->addRight(atrib, "pelos");
	else
		std::cout << "Side to add Fur is wrong\n";
}

void Being::defineFur() {
	singleFur(Side::left);
	singleFur(Side::right);
}

str Being::dominance(str atrib) {
    // Simply compares the strings of a being structure to
    // define its phenotype
    str gene1 = structure->leftInfo(atrib);
    str gene2 = structure->rightInfo(atrib);
    // Only compares the first letter of each being
    if (gene1.compare(0, 1, gene2, 0, 1) < 0 )
        return gene1;
    else if (gene1.compare(0, 1, gene2, 0, 1) > 0 )
        return gene2;
    else
        return gene1;
}

void Being::describe() {
    // Used only to print the being description
    str EyeColor = dominance("Cor");
    str EyeFormat = dominance("formato");
    str HairColor = dominance("cor");
    str HairType = dominance("tipo");
    str Arms = dominance("braços");
    str Legs = dominance("pernas");
    str Neck = dominance("pescoço");
    str Fur = dominance("pelos");
    std::cout << "\n\nO ente de id "<< id << " de pais " << parent_1 << " e " << parent_2;
    std::cout << "\ntem as seguintes características: \n";
    std::cout << "\tcor de olhos " << EyeColor << " em formato " << EyeFormat << ", \n";
    std::cout << "\tcabelo " << HairColor << " do tipo " << HairType << ", \n";
    std::cout << "\tbraços são " << Arms << " e as pernas são " << Legs << ", \n";
    std::cout << "\to pescoço é " << Neck << " enquanto o peito é " << Fur << ". \n\n";
}
