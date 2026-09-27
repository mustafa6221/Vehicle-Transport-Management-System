#include <stdio.h>
#include <string.h>

#define MAX_TRIPS 100

struct Trip
{
    int tripID;
    int vehicleID;
    int driverID;
    char source[50];
    char destination[50];
    char date[20];
    char status[20];
};

struct Trip trips[MAX_TRIPS];
int tripCount = 0;

void trip_menu();
void create_trip();
void view_trip_history();
void search_trip();

void trip_menu()
{
    int choice;

    do
    {
        printf("\n========== TRIP MANAGEMENT ==========\n");
        printf("1. Create Trip\n");
        printf("2. View Trip History\n");
        printf("3. Search Trip\n");
        printf("4. Back\n");
        printf("=====================================\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                create_trip();
                break;

            case 2:
                view_trip_history();
                break;

            case 3:
                search_trip();
                break;

            case 4:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);
}

void create_trip()
{
    if(tripCount >= MAX_TRIPS)
    {
        printf("Trip storage is full.\n");
        return;
    }

    printf("\n========== CREATE TRIP ==========\n");

    trips[tripCount].tripID = tripCount + 1;

    printf("Enter Vehicle ID: ");
    scanf("%d", &trips[tripCount].vehicleID);

    printf("Enter Driver ID: ");
    scanf("%d", &trips[tripCount].driverID);

    printf("Enter Source: ");
    scanf(" %[^\n]", trips[tripCount].source);

    printf("Enter Destination: ");
    scanf(" %[^\n]", trips[tripCount].destination);

    printf("Enter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", trips[tripCount].date);

    strcpy(trips[tripCount].status, "Completed");

    tripCount++;

    printf("\nTrip created successfully.\n");
    printf("Trip ID: %d\n", tripCount);
}

void view_trip_history()
{
    int i;

    if(tripCount == 0)
    {
        printf("\nNo trip records available.\n");
        return;
    }

    printf("\n================ TRIP HISTORY ================\n");

    for(i = 0; i < tripCount; i++)
    {
        printf("\nTrip ID       : %d\n", trips[i].tripID);
        printf("Vehicle ID    : %d\n", trips[i].vehicleID);
        printf("Driver ID     : %d\n", trips[i].driverID);
        printf("Source        : %s\n", trips[i].source);
        printf("Destination   : %s\n", trips[i].destination);
        printf("Date          : %s\n", trips[i].date);
        printf("Status        : %s\n", trips[i].status);
        printf("----------------------------------------------\n");
    }
}

void search_trip()
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Trip ID to search: ");
    scanf("%d", &id);

    for(i = 0; i < tripCount; i++)
    {
        if(trips[i].tripID == id)
        {
            printf("\n========== TRIP FOUND ==========\n");
            printf("Trip ID       : %d\n", trips[i].tripID);
            printf("Vehicle ID    : %d\n", trips[i].vehicleID);
            printf("Driver ID     : %d\n", trips[i].driverID);
            printf("Source        : %s\n", trips[i].source);
            printf("Destination   : %s\n", trips[i].destination);
            printf("Date          : %s\n", trips[i].date);
            printf("Status        : %s\n", trips[i].status);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Trip not found.\n");
    }
}
