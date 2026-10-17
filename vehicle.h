#ifndef VEHICLE_H
#define VEHICLE_H
#define MAX_VEHICLES 100

typedef struct {
    int vehicle_id;
    char model[50];
    char plate_number[20];
    char status[20];
    char fuel_type[20];
} Vehicle;

extern Vehicle fleet[MAX_VEHICLES];
extern int vehicle_count;
void vehicle_menu(void);
void load_vehicles(void);
void save_vehicles(void);
#endif
