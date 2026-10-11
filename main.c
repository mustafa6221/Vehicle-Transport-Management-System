#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicle.h"
#include "driver.h"
#include "trip.h"

int main(void)
{
    int choice;
    load_vehicles();
    load_drivers();
    load_trips();

    do {
        printf("\n===== VEHICLE AND TRANSPORT MANAGEMENT SYSTEM =====\n");
        printf("1. Vehicle Management\n");
        printf("2. Driver Management\n");
        printf("3. Trip Management\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: vehicle_menu(); break;
            case 2: driver_menu(); break;
            case 3: trip_menu(); break;
            case 0: printf("Exiting system. Records are saved in text files.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
