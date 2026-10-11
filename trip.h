#ifndef TRIP_H
#define TRIP_H
#define MAX_TRIPS 100

struct Trip {
    int tripID;
    int vehicleID;
    int driverID;
    char source[50];
    char destination[50];
    char date[20];
    char status[20];
};

extern struct Trip trips[MAX_TRIPS];
extern int tripCount;
void trip_menu(void);
void load_trips(void);
void save_trips(void);
#endif
