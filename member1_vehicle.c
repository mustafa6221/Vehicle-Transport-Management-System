#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEHICLES 100

// Define the Vehicle struct
typedef struct {
    int vehicle_id;
    char model[50];
    char plate_number[20];
    char status[20];    // e.g., "Available", "In Use", "Maintenance"
    char fuel_type[20]; // e.g., "Petrol", "Diesel", "Electric"
} Vehicle;

// Global array and tracking counter
Vehicle fleet[MAX_VEHICLES];
int vehicle_count = 0;

// Function Prototypes
void addVehicle();
void viewVehicles();
void searchVehicle();
void updateVehicle();
void deleteVehicle();
void checkAvailability();
void displayMenu();
void toLowerCase(char *str);

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        getchar(); // Consume trailing newline

        switch (choice) {
            case 1:
                addVehicle();
                break;
            case 2:
                viewVehicles();
                break;
            case 3:
                searchVehicle();
                break;
            case 4:
                updateVehicle();
                break;
            case 5:
                deleteVehicle();
                break;
            case 6:
                checkAvailability();
                break;
            case 7:
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please select between 1 and 7.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n=== TRANSPORT MANAGEMENT SYSTEM ===\n");
    printf("1. Add Vehicle\n");
    printf("2. View All Vehicles\n");
    printf("3. Search Vehicle\n");
    printf("4. Update Vehicle\n");
    printf("5. Delete Vehicle\n");
    printf("6. Check Vehicle Availability\n");
    printf("7. Exit\n");
    printf("===================================\n");
}

void addVehicle() {
    int i;
    Vehicle v;

    if (vehicle_count >= MAX_VEHICLES) {
        printf("Error: Fleet capacity full!\n");
        return;
    }

    printf("\n--- Add New Vehicle ---\n");
    printf("Enter Vehicle ID: ");
    scanf("%d", &v.vehicle_id);
    getchar();

    // Check for duplicate ID
    for (i = 0; i < vehicle_count; i++) {
        if (fleet[i].vehicle_id == v.vehicle_id) {
            printf("Error: Vehicle ID %d already exists!\n", v.vehicle_id);
            return;
        }
    }

    printf("Enter Model: ");
    fgets(v.model, sizeof(v.model), stdin);
    v.model[strcspn(v.model, "\n")] = '\0';

    printf("Enter Plate Number: ");
    fgets(v.plate_number, sizeof(v.plate_number), stdin);
    v.plate_number[strcspn(v.plate_number, "\n")] = '\0';

    printf("Enter Status (Available/In Use/Maintenance): ");
    fgets(v.status, sizeof(v.status), stdin);
    v.status[strcspn(v.status, "\n")] = '\0';

    printf("Enter Fuel Type (Petrol/Diesel/Electric): ");
    fgets(v.fuel_type, sizeof(v.fuel_type), stdin);
    v.fuel_type[strcspn(v.fuel_type, "\n")] = '\0';

    fleet[vehicle_count] = v;
    vehicle_count++;

    printf("Vehicle added successfully!\n");
}

void viewVehicles() {
    int i;

    if (vehicle_count == 0) {
        printf("\nNo vehicles found in system.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-15s %-10s\n", "ID", "Model", "Plate No.", "Status", "Fuel Type");
    printf("-----------------------------------------------------------------------\n");

    for (i = 0; i < vehicle_count; i++) {
        printf("%-10d %-20s %-15s %-15s %-10s\n",
               fleet[i].vehicle_id,
               fleet[i].model,
               fleet[i].plate_number,
               fleet[i].status,
               fleet[i].fuel_type);
    }
}

void searchVehicle() {
    int i, id;

    if (vehicle_count == 0) {
        printf("\nNo vehicles available to search.\n");
        return;
    }

    printf("\nEnter Vehicle ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < vehicle_count; i++) {
        if (fleet[i].vehicle_id == id) {
            printf("\nVehicle Found:\n");
            printf("ID:          %d\n", fleet[i].vehicle_id);
            printf("Model:       %s\n", fleet[i].model);
            printf("Plate No:    %s\n", fleet[i].plate_number);
            printf("Status:      %s\n", fleet[i].status);
            printf("Fuel Type:   %s\n", fleet[i].fuel_type);
            return;
        }
    }

    printf("Vehicle with ID %d not found.\n", id);
}

void updateVehicle() {
    int i, id;

    if (vehicle_count == 0) {
        printf("\nNo vehicles available to update.\n");
        return;
    }

    printf("\nEnter Vehicle ID to update: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < vehicle_count; i++) {
        if (fleet[i].vehicle_id == id) {
            printf("Enter New Model: ");
            fgets(fleet[i].model, sizeof(fleet[i].model), stdin);
            fleet[i].model[strcspn(fleet[i].model, "\n")] = '\0';

            printf("Enter New Plate Number: ");
            fgets(fleet[i].plate_number, sizeof(fleet[i].plate_number), stdin);
            fleet[i].plate_number[strcspn(fleet[i].plate_number, "\n")] = '\0';

            printf("Enter New Status: ");
            fgets(fleet[i].status, sizeof(fleet[i].status), stdin);
            fleet[i].status[strcspn(fleet[i].status, "\n")] = '\0';

            printf("Enter New Fuel Type: ");
            fgets(fleet[i].fuel_type, sizeof(fleet[i].fuel_type), stdin);
            fleet[i].fuel_type[strcspn(fleet[i].fuel_type, "\n")] = '\0';

            printf("Vehicle record updated successfully!\n");
            return;
        }
    }

    printf("Vehicle with ID %d not found.\n", id);
}

void deleteVehicle() {
    int i, j, id;

    if (vehicle_count == 0) {
        printf("\nNo vehicles available to delete.\n");
        return;
    }

    printf("\nEnter Vehicle ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < vehicle_count; i++) {
        if (fleet[i].vehicle_id == id) {
            // Shift remaining elements left
            for (j = i; j < vehicle_count - 1; j++) {
                fleet[j] = fleet[j + 1];
            }
            vehicle_count--;
            printf("Vehicle with ID %d deleted successfully.\n", id);
            return;
        }
    }

    printf("Vehicle with ID %d not found.\n", id);
}

// Helper function to convert string to lowercase for comparison
void toLowerCase(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void checkAvailability() {
    int i;
    int available_count = 0;
    char temp_status[20];

    if (vehicle_count == 0) {
        printf("\nNo vehicles in the system.\n");
        return;
    }

    printf("\n--- Available Vehicles ---\n");
    printf("%-10s %-20s %-15s\n", "ID", "Model", "Plate No.");
    printf("------------------------------------------\n");

    for (i = 0; i < vehicle_count; i++) {
        strcpy(temp_status, fleet[i].status);
        toLowerCase(temp_status);

        if (strcmp(temp_status, "available") == 0) {
            printf("%-10d %-20s %-15s\n", fleet[i].vehicle_id, fleet[i].model, fleet[i].plate_number);
            available_count++;
        }
    }

    if (available_count == 0) {
        printf("No vehicles are currently available.\n");
    } else {
        printf("Total Available: %d\n", available_count);
    }
}
