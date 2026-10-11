#ifndef DRIVER_H
#define DRIVER_H
#define MAX_DRIVERS 100
#define NAME_LEN 50
#define LICENSE_LEN 20
#define VEHICLE_LEN 20

typedef struct {
    int id;
    char name[NAME_LEN];
    char license_number[LICENSE_LEN];
    char assigned_vehicle_id[VEHICLE_LEN];
    int is_active;
} Driver;

extern Driver drivers[MAX_DRIVERS];
extern int driver_count;
void driver_menu(void);
void load_drivers(void);
void save_drivers(void);
#endif
