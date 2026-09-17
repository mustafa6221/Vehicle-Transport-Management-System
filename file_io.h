/* file_io.h
   Author: Muhammad Sarim
   Week 1 - File handling design (headers only, implementation in Week 5)
*/

#ifndef FILE_IO_H
#define FILE_IO_H

#include "structures.h"

#define VEHICLE_FILE "vehicles.dat"
#define DRIVER_FILE  "drivers.dat"
#define TRIP_FILE    "trips.dat"

/* Save functions - to be implemented in Week 5 */
void saveVehicles(void);
void saveDrivers(void);
void saveTrips(void);

/* Load functions - to be implemented in Week 5 */
void loadVehicles(void);
void loadDrivers(void);
void loadTrips(void);

#endif
