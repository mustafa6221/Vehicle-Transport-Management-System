#include <stdio.h>
#include <string.h>
#include "driver.h"

Driver drivers[MAX_DRIVERS];
int driver_count = 0;

static void read_line(const char *prompt, char *out, int size)
{
    printf("%s", prompt);
    if (fgets(out, size, stdin) == NULL) { out[0] = '\0'; return; }
    out[strcspn(out, "\n")] = '\0';
}

void load_drivers(void)
{
    FILE *fp = fopen("drivers.txt", "r");
    char line[256];
    driver_count = 0;
    if (!fp) return;
    while (driver_count < MAX_DRIVERS && fgets(line, sizeof line, fp)) {
        Driver d;
        if (sscanf(line, "%d|%49[^|]|%19[^|]|%19[^|]|%d", &d.id, d.name, d.license_number, d.assigned_vehicle_id, &d.is_active) == 5)
            drivers[driver_count++] = d;
    }
    fclose(fp);
}

void save_drivers(void)
{
    FILE *fp = fopen("drivers.txt", "w");
    int i;
    if (!fp) { printf("Error saving drivers.\n"); return; }
    for (i = 0; i < driver_count; i++)
        fprintf(fp, "%d|%s|%s|%s|%d\n", drivers[i].id, drivers[i].name, drivers[i].license_number, drivers[i].assigned_vehicle_id, drivers[i].is_active);
    fclose(fp);
}

static int find_driver(int id)
{
    int i;
    for (i = 0; i < driver_count; i++) if (drivers[i].id == id && drivers[i].is_active) return i;
    return -1;
}

static int next_driver_id(void)
{
    int i, max_id = 0;
    for (i = 0; i < driver_count; i++) if (drivers[i].id > max_id) max_id = drivers[i].id;
    return max_id + 1;
}

static void add_driver(void)
{
    Driver d;
    if (driver_count >= MAX_DRIVERS) { printf("Driver storage is full.\n"); return; }
    d.id = next_driver_id();
    printf("New Driver ID: %d\n", d.id);
    read_line("Enter Driver Name: ", d.name, sizeof d.name);
    read_line("Enter License Number: ", d.license_number, sizeof d.license_number);
    strcpy(d.assigned_vehicle_id, "Unassigned");
    d.is_active = 1;
    drivers[driver_count++] = d;
    save_drivers();
    printf("Driver added and saved.\n");
}

static void display_drivers(void)
{
    int i, shown = 0;
    printf("\n%-5s %-25s %-18s %-20s\n", "ID", "Name", "License", "Assigned Vehicle");
    for (i = 0; i < driver_count; i++) if (drivers[i].is_active) {
        printf("%-5d %-25s %-18s %-20s\n", drivers[i].id, drivers[i].name, drivers[i].license_number, drivers[i].assigned_vehicle_id);
        shown++;
    }
    if (!shown) printf("No active driver records.\n");
}

static void search_driver(void)
{
    int id, i;
    printf("Enter Driver ID: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_driver(id);
    if (i < 0) { printf("Active driver not found.\n"); return; }
    printf("ID: %d\nName: %s\nLicense: %s\nAssigned Vehicle: %s\n", drivers[i].id, drivers[i].name, drivers[i].license_number, drivers[i].assigned_vehicle_id);
}

static void update_driver(void)
{
    int id, i;
    printf("Enter Driver ID to update: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_driver(id);
    if (i < 0) { printf("Active driver not found.\n"); return; }
    read_line("New Name: ", drivers[i].name, sizeof drivers[i].name);
    read_line("New License Number: ", drivers[i].license_number, sizeof drivers[i].license_number);
    save_drivers();
    printf("Driver updated and saved.\n");
}

static void delete_driver(void)
{
    int id, i;
    printf("Enter Driver ID to delete: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_driver(id);
    if (i < 0) { printf("Active driver not found.\n"); return; }
    drivers[i].is_active = 0;
    save_drivers();
    printf("Driver marked inactive and saved.\n");
}

static void assign_driver(void)
{
    int id, i;
    printf("Enter Driver ID: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_driver(id);
    if (i < 0) { printf("Active driver not found.\n"); return; }
    read_line("Enter Vehicle ID or plate (or Unassigned): ", drivers[i].assigned_vehicle_id, sizeof drivers[i].assigned_vehicle_id);
    save_drivers();
    printf("Assignment saved. Note: vehicle existence is not yet cross-validated.\n");
}

void driver_menu(void)
{
    int choice;
    do {
        printf("\n--- DRIVER MANAGEMENT ---\n1. Add Driver\n2. View Drivers\n3. Search Driver\n4. Update Driver\n5. Delete Driver\n6. Assign Driver to Vehicle\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); choice = -1; continue; }
        while (getchar() != '\n');
        switch (choice) {
            case 1: add_driver(); break;
            case 2: display_drivers(); break;
            case 3: search_driver(); break;
            case 4: update_driver(); break;
            case 5: delete_driver(); break;
            case 6: assign_driver(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
