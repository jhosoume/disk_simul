/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"

void showFAT(std::vector <fatlist> const &files, std::vector <fatent> const &sectors) {
	std::cout << std::left << std::setw(20) << "\nNome: "; 
	std::cout << std::left << std::setw(20) <<   "Tamanho em Disco: ";
	std::cout << std::left << std::setw(20) <<   "Localização:" << std::endl;
    for (fatlist file : files) {
        file_sectors secs = fileSectors(file.first_sector, sectors); 
	    std::cout << std::left << std::setw(20) << file.file_name; 
        std::cout << std::left << std::setw(20) << secs.size; 
        std::cout << std::left << std::setw(20) 
            << listToString(secs.sectors) << std::endl; 
    }
}

file_sectors fileSectors(unsigned int first_sector, 
                            std::vector <fatent> sectors) {
    file_sectors fsecs = file_sectors(1, {first_sector});
    fatent current_sec = sectors.at(first_sector);
    while (current_sec.next > 0) {
        fsecs.size++;
        fsecs.sectors.push_back(current_sec.next);
        current_sec = sectors.at(current_sec.next);
    }
    fsecs.size *= sector_size;
    return fsecs;
}

void writeFile(str const &file_name, std::vector <fatlist> &file_list, 
                   std::vector <fatent> &fat, std::vector <track_array> &cylinders) {
    unsigned int size = 0;
    unsigned int num_secs = 1;
    char letter;
    unsigned int sector_indx = freeCluster(fat);
    unsigned int previous_indx = sector_indx;
    fat.at(sector_indx).mark();
    sector_pos sector_pos = getPosFromIndx(sector_indx);
    file_list.push_back(fatlist(file_name, sector_indx));
    std::fstream fin(file_name, std::fstream::in);
    while (fin >> std::noskipws >> letter) {
        //std::cout << "\n Onde: " << sector_pos.cylinder << sector_pos.track << sector_pos.sector << " " << size << std::endl;
        cylinders.at(sector_pos.cylinder).setData(sector_pos.track, sector_pos.sector, size, letter);
        ++size;
        if (size % sector_size == 0) {
            previous_indx = sector_indx;
            if (num_secs % cluster_size == 0) {
                sector_indx = getIndxFromPos(begOfCluster(nextFreeCluster(sector_pos, fat)));
            } else {
                sector_indx = nextFreeSector(sector_pos, fat);
            }
            fat.at(previous_indx).writeSector(sector_indx);
            fat.at(sector_indx).mark();
            sector_pos = getPosFromIndx(sector_indx);
            size = 0;
            ++num_secs;
        }
    }
    fat.at(sector_indx).writeSector(1, -1);
    closeCluster(sector_indx, fat);
}


void readFile(str filename, std::vector <fatlist> &file_list,
                   std::vector <fatent> &fat, std::vector <track_array> &cylinders) {
    //TODO
    fatlist fat_entry = findFat(filename, file_list);  
	fatent current_sec = fat.at(fat_entry.first_sector);
    sector_pos pos = getPosFromIndx(fat_entry.first_sector);
    std::ofstream outfile;
    outfile.open("read/" + filename);
    if (outfile.is_open()) {
        do {
            for (size_t byte = 0; byte < sector_size; ++byte ) {
                outfile << cylinders[pos.cylinder].getData(pos.track, pos.sector, byte);
            }
            current_sec = fat.at(current_sec.next);
            if (current_sec.next > 0) {
                std::cout << "\n CURRENT SEC " << current_sec.next;
                pos = getPosFromIndx(current_sec.next);
            }
        } while (current_sec.eof < 1 && current_sec.next > 0); 
        outfile.close();
    } else {
        std::cout << "Arquivo não pode ser aberto para escrita";
    }
}

void deleteFile(str filename, std::vector <fatlist> &file_list,
                   std::vector <fatent> &fat, std::vector <track_array> &cylinders) {
    fatlist fat_entry = findFat(filename, file_list);  
	unsigned int current_sec = fat_entry.first_sector;
	unsigned int next_sec = fat.at(current_sec).next;
    do {
        fat.at(current_sec).free();
        current_sec = next_sec;
        next_sec = fat.at(current_sec).next;
    } while (fat.at(next_sec).next > 0); 
    fat.at(current_sec).free();
    fat.at(next_sec).free();
    eraseFat(filename, file_list);
}

void closeCluster(unsigned int num_sector, std::vector <fatent> &sectors) {
    //TODO Write empty spaces with null
    if ((num_sector + 1) % cluster_size != 0) {
        unsigned int end = ((num_sector / cluster_size) + 1) * cluster_size;
        size_t indx = num_sector;
        for (; indx < end - 1; ++indx) {
            sectors.at(indx).writeSector(indx + 1);
        }
        sectors.at(indx).writeSector(-1);
    }
}


size_t freeCluster(std::vector <fatent> const &sectors) {
    unsigned int indx;
    for (size_t cylinder = 0; cylinder < num_cylinder; cylinder++) {
        for (size_t track = 0; track < track_per_cylinder; track++) {
            for (size_t cur_sector = 0; cur_sector < sec_per_track; cur_sector += 4) {
                indx = getIndxFromPos(sector_pos(cylinder, track, cur_sector));
                if(sectors.at(indx).used != 1) {
                    return indx;
                }
            }
        }
    }
    throw "Sem setor livre";
}

sector_pos begOfCluster(sector_pos pos) {
    pos.sector = (pos.sector / cluster_size) * cluster_size;
    return pos;
}

sector_pos begOfCluster(unsigned int indx) {
    return begOfCluster(getPosFromIndx(indx));
}

size_t nextFreeCluster(sector_pos pos, std::vector <fatent> const &sectors) {
    fatent sector;
    unsigned int indx;
    for (size_t cylinder = pos.cylinder; cylinder < num_cylinder; 
                                                            cylinder++) {
        for (size_t cur_sector = pos.sector; cur_sector < sec_per_track; 
                                               cur_sector++) {
            for (size_t track = pos.track; track < track_per_cylinder; ++track) {
                indx = getIndxFromPos(sector_pos(cylinder, track, cur_sector));
                sector = sectors.at(indx);
                if(sector.used != 1) {
                    return indx;
                }
                pos.track = 0;
            }
            pos.sector = 0;
        }
    }
    throw "Sem setor livre";
}

size_t nextFreeSector(sector_pos pos, std::vector <fatent> const &sectors) {
    fatent sector;
    unsigned int indx;
    for (size_t track = pos.track; track < track_per_cylinder; track++) {
        for (size_t cylinder = pos.cylinder; cylinder < num_cylinder; 
                                                                cylinder++) {
            for (size_t cur_sector = pos.sector; cur_sector < sec_per_track; 
                                                       cur_sector++) {
                indx = getIndxFromPos(sector_pos(cylinder, track, cur_sector));
                sector = sectors.at(indx);
                if(sector.used != 1) {
                    return indx;
                }
                pos.sector = 0;
            }
            pos.cylinder = 0;
        }
    }
    throw "Sem setor livre";
}

void block::setData(unsigned int byte, unsigned char data) {
    this->bytes_s[byte] = data;
}

void sector_array::setData(unsigned int block, unsigned int byte, unsigned char data) {
    this->sector[block].setData(byte, data);
}

void track_array::setData(unsigned int track, unsigned int block, unsigned int byte, unsigned char data) {
    this->track[track].setData(block, byte, data);
}

unsigned char block::getData(unsigned int byte) {
    return this->bytes_s[byte];
}


unsigned char sector_array::getData(unsigned int block, unsigned int byte) {
    return this->sector[block].getData(byte);
}

unsigned char track_array::getData(unsigned int track, unsigned int block, unsigned int byte) {
    return this->track[track].getData(block, byte);
}


void fatent::mark() {
    this->used = 1;
}

void fatent::writeSector(unsigned int next) {
    this->used = 1; this->next = next;
}

void fatent::writeSector(unsigned int eof, int next) {
    this->used = 1; this->eof = eof; this->next = next;
}

void fatent::print() {
    std::cout << "\nU:" << this->used << "EOF:" << this->eof << "N:" << this->next << std::endl;
}

void fatent::free() {
    this->used = 0; this->eof = 0; this->next = -1;
}

void printSectors(std::vector <fatent> const &fat) {
    std::cout << "\n\nPrinting Secs\n";
    fatent sec;
    for (size_t indx = 0; indx < fat.size(); ++indx) {
        sec = fat[indx];
        std::cout << "\nSec " << indx;
        sec.print();
    }

}

sector_pos getPosFromIndx(unsigned int indx) {
    unsigned int tracks;
    std::cout << "\nINDX " << indx;
    if (indx > num_cylinder * track_per_cylinder * sec_per_track)
        throw "Índice do setor ultrapassa o número de setores do disco";
    sector_pos positions = sector_pos();
    tracks = indx / sec_per_track;
    positions.sector = indx % sec_per_track;
    positions.track = tracks % track_per_cylinder;
    positions.cylinder = tracks / track_per_cylinder;
    return positions;
}

unsigned int getIndxFromPos(sector_pos pos) {
    return pos.sector + (pos.track * sec_per_track) + 
        (pos.cylinder * track_per_cylinder * sec_per_track);
}

fatlist findFat(str const &name, std::vector <fatlist> &fat_list) {
    for (fatlist file : fat_list) {
        if (file.file_name == name)
            return file;
    }
    return fatlist();
}

bool inFat(str const &name, std::vector <fatlist> &fat_list) {
    for (fatlist file : fat_list) {
        if (file.file_name == name)
            return true;
    }
    return false;
}


void eraseFat(str const &name, std::vector <fatlist> &fat_list) {
    fat_list.erase(
        std::remove_if(fat_list.begin(), fat_list.end(), 
            [&name](fatlist file) -> bool { return file.file_name == name; }),
        fat_list.end()
    );
}

void run(std::vector <fatlist> &file_list, 
                   std::vector <fatent> &fat, std::vector <track_array> &cyls) {
    //TODO
    unsigned long option;
    str name;
    while (true) {
        printOptions();
        option = getChoice();
        switch(option) {
            case 1: name = getFileName();
                    if (inFat(name, file_list))
                        std::cout << 
                                "\n[SAVED]Arquivo já está salvo no disco\n";
                    else
                         writeFile(name, file_list, fat, cyls); 
                    break;
            case 2: name = getFileName();
                    if (!inFat(name, file_list))
                        std::cout << 
                            "\n[NOT FOUND]Não há arquivo com este nome\n";
                    else
                        readFile(name, file_list, fat, cyls);
                    break;
            case 3: name = getFileName();
                    if (!inFat(name, file_list)) 
                        std::cout << 
                            "\n[NOT FOUND]Não há arquivo com este nome\n";
                    else
                        deleteFile(name, file_list, fat, cyls);
                    break;
            case 4: showFAT(file_list, fat);
                    break;
            case 5: return;
        }
    }
}

Disk::Disk() 
    : id{"-1"} {}

str Disk::getId(){
    return id;
}
