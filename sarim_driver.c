#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Driver drivers[MAX_DRIVERS];
int driver_count = 0;

void driver_menu(void);
void add_driver(void);
void display_drivers(void);
void search_driver(void);
void update_driver_info(void);
void delete_driver(void);
void assign_driver_to_vehicle(void);
int get_valid_int(const char *prompt);
void get_valid_string(const char *prompt, char *output, int max_length);

int get_valid_int(const char *prompt) {
    int value;
    char buffer[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            }
        }
        printf("Invalid input! Please enter a valid integer number.\n");
    }
}

void get_valid_string(const char *prompt, char *output, int max_length) {
    printf("%s", prompt);
    if (fgets(output, max_length, stdin) != NULL) {
        size_t len = strlen(output);
        if (len > 0 && output[len - 1] == '\n') {
            output[len - 1] = '\0';
        }
    }
}

void add_driver(void) {
    if (driver_count >= MAX_DRIVERS) {
        printf("\nError: Driver registry is full.\n");
        return;
    }

    Driver new_driver;
    new_driver.id = driver_count + 1;

    printf("\n--- Add New Driver ---\n");
    get_valid_string("Enter Driver Name: ", new_driver.name, NAME_LEN);
    get_valid_string("Enter License Number: ", new_driver.license_number, LICENSE_LEN);
    strcpy(new_driver.assigned_vehicle_id, "Unassigned");
    new_driver.is_active = 1;

    drivers[driver_count] = new_driver;
    driver_count++;

    printf("Driver added successfully! (Assigned ID: %d)\n", new_driver.id);
}

void display_drivers(void) {
    if (driver_count == 0) {
        printf("\nNo driver records found.\n");
        return;
    }

    printf("\n%-5s %-25s %-15s %-15s\n", "ID", "Name", "License No.", "Assigned Vehicle");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < driver_count; i++) {
        if (drivers[i].is_active) {
            printf("%-5d %-25s %-15s %-15s\n",
                   drivers[i].id,
                   drivers[i].name,
                   drivers[i].license_number,
                   drivers[i].assigned_vehicle_id);
        }
    }
}

void search_driver(void) {
    if (driver_count == 0) {
        printf("\nNo driver records available to search.\n");
        return;
    }

    int search_id = get_valid_int("\nEnter Driver ID to search: ");
    for (int i = 0; i < driver_count; i++) {
        if (drivers[i].id == search_id && drivers[i].is_active) {
            printf("\n--- Driver Found ---\n");
            printf("ID: %d\n", drivers[i].id);
            printf("Name: %s\n", drivers[i].name);
            printf("License Number: %s\n", drivers[i].license_number);
            printf("Assigned Vehicle: %s\n", drivers[i].assigned_vehicle_id);
            return;
        }
    }
    printf("Driver with ID %d not found.\n", search_id);
}

void update_driver_info(void) {
    int target_id = get_valid_int("\nEnter Driver ID to update: ");
    for (int i = 0; i < driver_count; i++) {
        if (drivers[i].id == target_id && drivers[i].is_active) {
            printf("\nUpdating records for %s...\n", drivers[i].name);
            get_valid_string("Enter New Name: ", drivers[i].name, NAME_LEN);
            get_valid_string("Enter New License Number: ", drivers[i].license_number, LICENSE_LEN);
            printf("Driver details updated successfully.\n");
            return;
        }
    }
    printf("Driver with ID %d not found.\n", target_id);
}

void delete_driver(void) {
    int target_id = get_valid_int("\nEnter Driver ID to delete: ");
    for (int i = 0; i < driver_count; i++) {
        if (drivers[i].id == target_id && drivers[i].is_active) {
            drivers[i].is_active = 0;
            printf("Driver record for ID %d deleted successfully.\n", target_id);
            return;
        }
    }
    printf("Driver with ID %d not found.\n", target_id);
}

void assign_driver_to_vehicle(void) {
    int target_id = get_valid_int("\nEnter Driver ID: ");
    for (int i = 0; i < driver_count; i++) {
        if (drivers[i].id == target_id && drivers[i].is_active) {
            get_valid_string("Enter Vehicle ID/Plate Number to assign: ", 
                             drivers[i].assigned_vehicle_id, 
                             VEHICLE_LEN);
            printf("Vehicle assigned successfully to driver %s!\n", drivers[i].name);
            return;
        }
    }
    printf("Driver with ID %d not found.\n", target_id);
}

void driver_menu(void) {
    int choice;
    do {
        printf("\n=============================\n");
        printf("    DRIVER MANAGEMENT MENU   \n");
        printf("=============================\n");
        printf("1. Add Driver\n");
        printf("2. View Driver List\n");
        printf("3. Search Driver\n");
        printf("4. Update Driver Info\n");
        printf("5. Delete Driver Record\n");
        printf("6. Assign Driver to Vehicle\n");
        printf("0. Return / Exit\n");
        
        choice = get_valid_int("Enter your choice: ");

        switch (choice) {
            case 1:
                add_driver();
                break;
            case 2:
                display_drivers();
                break;
            case 3:
                search_driver();
                break;
            case 4:
                update_driver_info();
                break;
            case 5:
                delete_driver();
                break;
            case 6:
                assign_driver_to_vehicle();
                break;
            case 0:
                printf("Exiting Driver Module...\n");
                break;
            default:
                printf("Invalid choice! Please select options 0-6.\n");
        }
    } while (choice != 0);
}

int main(void) {
    driver_menu();
    return 0;
}
