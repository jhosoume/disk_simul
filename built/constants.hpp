#ifndef CONST
#define CONST

/* Constants to define the HD beeing used.
 * Virtual "Hardware" can be made here. */


/* Capacity */
const unsigned int num_cylinder = 4;
const unsigned int cluster_size = 4;
const unsigned int sector_size = 512;
const unsigned int sec_per_track = 60;
const unsigned int track_per_cylinder = 5;

/* Max storage accordingly to previous defined constants */
const unsigned int max_sectors = num_cylinder * track_per_cylinder * sec_per_track;
const unsigned int max_size = num_cylinder * track_per_cylinder * sec_per_track * sector_size;

/* Efficiency of the HD */
const double time_min_seek = 1.0; // ms
const double time_mean_seek = 4.0; // ms
const double time_transf = 12.0; // ms/track
const double time_latency = 6.0; //ms

#endif
