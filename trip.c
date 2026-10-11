#include <stdio.h>
#include <string.h>
#include "trip.h"

struct Trip trips[MAX_TRIPS];
int tripCount = 0;

static void read_line(const char *prompt, char *out, int size)
{
    printf("%s", prompt);
    if (fgets(out, size, stdin) == NULL) { out[0] = '\0'; return; }
    out[strcspn(out, "\n")] = '\0';
}

void load_trips(void)
{
    FILE *fp = fopen("trips.txt", "r");
    char line[256];
    tripCount = 0;
    if (!fp) return;
    while (tripCount < MAX_TRIPS && fgets(line, sizeof line, fp)) {
        struct Trip t;
        if (sscanf(line, "%d|%d|%d|%49[^|]|%49[^|]|%19[^|]|%19[^\n]", &t.tripID, &t.vehicleID, &t.driverID, t.source, t.destination, t.date, t.status) == 7)
            trips[tripCount++] = t;
    }
    fclose(fp);
}

void save_trips(void)
{
    FILE *fp = fopen("trips.txt", "w");
    int i;
    if (!fp) { printf("Error saving trips.\n"); return; }
    for (i = 0; i < tripCount; i++)
        fprintf(fp, "%d|%d|%d|%s|%s|%s|%s\n", trips[i].tripID, trips[i].vehicleID, trips[i].driverID, trips[i].source, trips[i].destination, trips[i].date, trips[i].status);
    fclose(fp);
}

static int find_trip(int id)
{
    int i;
    for (i = 0; i < tripCount; i++) if (trips[i].tripID == id) return i;
    return -1;
}

static void create_trip(void)
{
    struct Trip t;
    if (tripCount >= MAX_TRIPS) { printf("Trip storage is full.\n"); return; }
    printf("Enter Trip ID: ");
    if (scanf("%d", &t.tripID) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    if (t.tripID <= 0 || find_trip(t.tripID) >= 0) { printf("Trip ID must be positive and unique.\n"); return; }
    printf("Enter Vehicle ID: ");
    if (scanf("%d", &t.vehicleID) != 1 || t.vehicleID <= 0) { while (getchar() != '\n'); printf("Invalid Vehicle ID.\n"); return; }
    while (getchar() != '\n');
    printf("Enter Driver ID: ");
    if (scanf("%d", &t.driverID) != 1 || t.driverID <= 0) { while (getchar() != '\n'); printf("Invalid Driver ID.\n"); return; }
    while (getchar() != '\n');
    read_line("Enter Source (no | character): ", t.source, sizeof t.source);
    read_line("Enter Destination (no | character): ", t.destination, sizeof t.destination);
    read_line("Enter Date (DD/MM/YYYY): ", t.date, sizeof t.date);
    strcpy(t.status, "Planned");
    trips[tripCount++] = t;
    save_trips();
    printf("Trip created and saved. Trip ID: %d\n", t.tripID);
}

static void view_trip_history(void)
{
    int i;
    if (!tripCount) { printf("No trip records available.\n"); return; }
    for (i = 0; i < tripCount; i++)
        printf("\nTrip ID: %d\nVehicle ID: %d\nDriver ID: %d\nSource: %s\nDestination: %s\nDate: %s\nStatus: %s\n", trips[i].tripID, trips[i].vehicleID, trips[i].driverID, trips[i].source, trips[i].destination, trips[i].date, trips[i].status);
}

static void search_trip(void)
{
    int id, i;
    printf("Enter Trip ID to search: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_trip(id);
    if (i < 0) { printf("Trip not found.\n"); return; }
    printf("Trip ID: %d\nVehicle ID: %d\nDriver ID: %d\nSource: %s\nDestination: %s\nDate: %s\nStatus: %s\n", trips[i].tripID, trips[i].vehicleID, trips[i].driverID, trips[i].source, trips[i].destination, trips[i].date, trips[i].status);
}

static void update_trip_status(void)
{
    int id, i, choice;
    printf("Enter Trip ID to update: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid ID.\n"); return; }
    while (getchar() != '\n');
    i = find_trip(id);
    if (i < 0) { printf("Trip not found.\n"); return; }
    printf("1. Planned\n2. In Progress\n3. Completed\n4. Cancelled\nChoose status: ");
    if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); printf("Invalid choice.\n"); return; }
    while (getchar() != '\n');
    switch (choice) {
        case 1: strcpy(trips[i].status, "Planned"); break;
        case 2: strcpy(trips[i].status, "In Progress"); break;
        case 3: strcpy(trips[i].status, "Completed"); break;
        case 4: strcpy(trips[i].status, "Cancelled"); break;
        default: printf("Invalid status choice.\n"); return;
    }
    save_trips();
    printf("Trip status updated and saved.\n");
}

void trip_menu(void)
{
    int choice;
    do {
        printf("\n--- TRIP MANAGEMENT ---\n1. Create Trip\n2. View Trip History\n3. Search Trip\n4. Update Trip Status\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); choice = -1; continue; }
        while (getchar() != '\n');
        switch (choice) {
            case 1: create_trip(); break;
            case 2: view_trip_history(); break;
            case 3: search_trip(); break;
            case 4: update_trip_status(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}