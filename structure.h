/* structures.h
   Author: Muhib Haider
   Week 1 - Data structures for Vehicle, Driver, and Trip
*/

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_VEHICLES 100
#define MAX_DRIVERS  100
#define MAX_TRIPS    200
#define NAME_LEN     50
#define DATE_LEN     15

typedef enum {
    AVAILABLE,
    ASSIGNED,
    UNDER_MAINTENANCE
} VehicleStatus;

typedef struct {
    int vehicleID;
    char regNumber[20];
    char model[NAME_LEN];
    char type[NAME_LEN];      /* car, bus, truck, etc. */
    VehicleStatus status;
    int assignedDriverID;     /* -1 if not assigned */
} Vehicle;

typedef struct {
    int driverID;
    char name[NAME_LEN];
    char licenseNumber[20];
    char contactNumber[20];
    int assignedVehicleID;    /* -1 if not assigned */
} Driver;

typedef struct {
    int tripID;
    int vehicleID;
    int driverID;
    char source[NAME_LEN];
    char destination[NAME_LEN];
    char tripDate[DATE_LEN];
} Trip;

/* Global arrays and counters (declared here, defined in main.c) */
extern Vehicle vehicles[MAX_VEHICLES];
extern Driver drivers[MAX_DRIVERS];
extern Trip trips[MAX_TRIPS];

extern int vehicleCount;
extern int driverCount;
extern int tripCount;

#endif