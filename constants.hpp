#ifndef CONST
#define CONST

const unsigned int num_cylinder = 4;
const unsigned int cluster_size = 4;
const unsigned int seek_time = 4;
const unsigned int latency = 6;
const unsigned int transf = 12;
const unsigned int sector_size = 512;
const unsigned int sec_per_track = 60;
const unsigned int track_per_cylinder = 5;
const unsigned int max_sectors = num_cylinder * track_per_cylinder * sec_per_track;
const unsigned int max_size = num_cylinder * track_per_cylinder * sec_per_track * sector_size;

#endif
