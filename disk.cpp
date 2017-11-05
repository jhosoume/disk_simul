/*
 *  NOME: Juliana Mayumi Hosoume
 *  MATRICULA: 17/0003078
 *  MATÉRIA: Organização de Arquivos
 *  SEMESTRE: Segundo Semestre de 2017
*/

#include "disk.hpp"

void showFAT(std::vector <fatlist> files, std::vector <fatent> sectors) {
	std::cout << std::left << std::setw(20) << "Nome: "; 
	std::cout << std::left << std::setw(20) << "Tamanho em Disco: ";
	std::cout << std::left << std::setw(20) << "Localização:\n";
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
    while (current_sec.eof != 1) {
        fsecs.size++;
        fsecs.sectors.push_back(current_sec.next);
        current_sec = sectors.at(current_sec.next);
    }
    fsecs.size *= sector_size;
    return fsecs;
}

void writeFile(str file_name, std::vector <fatlist> file_list, 
                   std::vector <fatent> fat, track_array cylinders[]) {
    unsigned int size = 0;
    char letter;
    unsigned int sector_indx = freeCluster(fat);
    sector_pos sector_pos = getPosFromIndx(sector_indx);
    file_list.push_back(fatlist(file_name, sector_indx));
    std::fstream fin(file_name, std::fstream::in);
    while (fin >> std::noskipws >> letter) {
        cylinders[sector_pos.cylinder].track[sector_pos.track].
                   sector[sector_pos.sector].bytes_s[size] = letter; 
        size++;
        if (size % sector_size == 0) {
            sector_indx = nextFreeSector(sector_pos, fat);
            sector_pos = getPosFromIndx(sector_indx);
            fat.at(sector_indx).writeSector(0, sector_indx);
        }
    }
    fat.at(sector_indx).writeSector(1);
    closeCluster(sector_indx, fat);
}

void closeCluster(unsigned int num_sector, std::vector <fatent> sectors) {
    if (num_sector % cluster_size != 0) {
        unsigned int end = ((num_sector / cluster_size) + 1) * cluster_size;
        for (size_t indx = num_sector; indx < end; indx++) {
            sectors.at(indx).writeSector(1);
        }
    }
}


size_t freeCluster(std::vector <fatent> sectors) {
    fatent sector;
    unsigned int indx;
    for (size_t track = 0; track < track_per_cylinder; track++) {
        for (size_t cylinder = 0; cylinder < num_cylinder; cylinder++) {
            for (size_t cur_sector = 0; cur_sector < sec_per_track; cur_sector += 4) {
                indx = getIndxFromPos(sector_pos(cylinder, track, cur_sector));
                sector = sectors.at(indx);
                if(sector.used != 1) {
                    return indx;
                }
            }
        }
    }
    throw "Sem setor livre";
}

size_t nextFreeSector(sector_pos pos, std::vector <fatent> sectors) {
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
            }
        }
    }
    throw "Sem setor livre";
}



void fatent::writeSector(unsigned int eof) {
    this->writeSector(eof, -1);
}

void fatent::writeSector(unsigned int eof, int next) {
    this->used = 1; this->eof = eof; this->next = next;
}

sector_pos getPosFromIndx(unsigned int indx) {
    if (indx > num_cylinder * track_per_cylinder * sec_per_track)
        throw "Índice do setor ultrapassa o número de setores do disco";
    sector_pos positions = sector_pos();
    unsigned int tracks = indx / sec_per_track;
    positions.sector = indx % sec_per_track;
    positions.track = tracks % track_per_cylinder;
    positions.cylinder = tracks / track_per_cylinder;
    return positions;
}

unsigned int getIndxFromPos(sector_pos pos) {
    return pos.sector + (pos.track * sec_per_track) + 
        (pos.cylinder * track_per_cylinder * sec_per_track);
}

Disk::Disk() 
    : id{"-1"} {}

str Disk::getId(){
    return id;
}
