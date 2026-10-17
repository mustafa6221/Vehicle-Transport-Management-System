#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "vehicle.h"

Vehicle fleet[MAX_VEHICLES];
int vehicle_count = 0;

static void read_line(const char *prompt, char *out, int size)
{
    printf("%s", prompt);
    if (fgets(out, size, stdin) == NULL) { out[0] = '\0'; return; }
    out[strcspn(out, "\n")] = '\0';
}

void load_vehicles(void)
{
    FILE *fp = fopen("vehicles.txt", "r");
    char line[256];
    vehicle_count = 0;
    if (!fp) return;
    while (vehicle_count < MAX_VEHICLES && fgets(line, sizeof line, fp)) {
        Vehicle v;
        if (sscanf(line, "%d|%49[^|]|%19[^|]|%19[^|]|%19[^\n]", &v.vehicle_id, v.model, v.plate_number, v.status, v.fuel_type) == 5)
            fleet[vehicle_count++] = v;
    }
    fclose(fp);
}

void save_vehicles(void)
{
    FILE *fp = fopen("vehicles.txt", "w");
    int i;
    if (!fp) { printf("Error saving vehicles.\n"); return; }
    for (i = 0; i < vehicle_count; i++)
        fprintf(fp, "%d|%s|%s|%s|%s\n", fleet[i].vehicle_id, fleet[i].model, fleet[i].plate_number, fleet[i].status, fleet[i].fuel_type);
    fclose(fp);
}

static int find_vehicle(int id)
{
    int i;
    for (i = 0; i < vehicle_count; i++) if (fleet[i].vehicle_id == id) return i;
    return -1;
}

static void add_vehicle(void)
{
    Vehicle v;
    int id;
    if (vehicle_count >= MAX_VEHICLES) { printf("Vehicle storage is full.\n"); return; }
    printf("Enter Vehicle ID: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    if (id <= 0 || find_vehicle(id) >= 0) { printf("ID must be positive and unique.\n"); return; }
    v.vehicle_id = id;
    read_line("Enter Model: ", v.model, sizeof v.model);
    read_line("Enter Plate Number (no | character): ", v.plate_number, sizeof v.plate_number);
    read_line("Enter Status (Available/In Use/Maintenance): ", v.status, sizeof v.status);
    read_line("Enter Fuel Type (Petrol/Diesel/Electric): ", v.fuel_type, sizeof v.fuel_type);
    fleet[vehicle_count++] = v;
    save_vehicles();
    printf("Vehicle added and saved.\n");
}

static void view_vehicles(void)
{
    int i;
    if (!vehicle_count) { printf("No vehicles found.\n"); return; }
    printf("\n%-8s %-20s %-15s %-16s %-12s\n", "ID", "Model", "Plate", "Status", "Fuel");
    for (i = 0; i < vehicle_count; i++)
        printf("%-8d %-20s %-15s %-16s %-12s\n", fleet[i].vehicle_id, fleet[i].model, fleet[i].plate_number, fleet[i].status, fleet[i].fuel_type);
}

static void search_vehicle(void)
{
    int id, i;
    printf("Enter Vehicle ID: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_vehicle(id);
    if (i < 0) { printf("Vehicle not found.\n"); return; }
    printf("ID: %d\nModel: %s\nPlate: %s\nStatus: %s\nFuel: %s\n", fleet[i].vehicle_id, fleet[i].model, fleet[i].plate_number, fleet[i].status, fleet[i].fuel_type);
}

static void update_vehicle(void)
{
    int id, i;
    printf("Enter Vehicle ID to update: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_vehicle(id);
    if (i < 0) { printf("Vehicle not found.\n"); return; }
    read_line("New Model: ", fleet[i].model, sizeof fleet[i].model);
    read_line("New Plate Number: ", fleet[i].plate_number, sizeof fleet[i].plate_number);
    read_line("New Status: ", fleet[i].status, sizeof fleet[i].status);
    read_line("New Fuel Type: ", fleet[i].fuel_type, sizeof fleet[i].fuel_type);
    save_vehicles();
    printf("Vehicle updated and saved.\n");
}

static void delete_vehicle(void)
{
    int id, i, j;
    printf("Enter Vehicle ID to delete: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_vehicle(id);
    if (i < 0) { printf("Vehicle not found.\n"); return; }
    for (j = i; j < vehicle_count - 1; j++) fleet[j] = fleet[j + 1];
    vehicle_count--;
    save_vehicles();
    printf("Vehicle deleted and file updated.\n");
}

static void check_availability(void)
{
    int i, count = 0;
    char status[20];
    for (i = 0; i < vehicle_count; i++) {
        size_t j;
        strcpy(status, fleet[i].status);
        for (j = 0; status[j]; j++) status[j] = (char)tolower((unsigned char)status[j]);
        if (strcmp(status, "available") == 0) {
            printf("ID: %d | Model: %s | Plate: %s\n", fleet[i].vehicle_id, fleet[i].model, fleet[i].plate_number);
            count++;
        }
    }
    printf("Total available vehicles: %d\n", count);
}

void vehicle_menu(void)
{
    int choice;
    do {
        printf("\n--- VEHICLE MANAGEMENT ---\n1. Add Vehicle\n2. View Vehicles\n3. Search Vehicle\n4. Update Vehicle\n5. Delete Vehicle\n6. Check Availability\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); choice = -1; continue; }
        while (getchar() != '\n');
        switch (choice) {
            case 1: add_vehicle(); break;
            case 2: view_vehicles(); break;
            case 3: search_vehicle(); break;
            case 4: update_vehicle(); break;
            case 5: delete_vehicle(); break;
            case 6: check_availability(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}