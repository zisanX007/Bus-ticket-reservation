#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int seatNumber;
    int isBooked;
    char bookedBy[50];
} Seat;

Seat seats[20]; // Array to store seat availability (20 seats)
int totalSeats = 20;

// Global variable to track login state
int loggedIn = 0; // 0 = Not logged in, 1 = Logged in
char currentUser[50]; // To store the currently logged-in user's username

// Function Prototypes
void registration();
int login();
void viewSeats();
int main() {
    int choice;
    while (1) {
    printf("Welcome to the Bus Ticket Reservation System!\n");
    printf("\n1. Register\n2. Login\n3. View Seats\n  ");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registration();
            break;
        case 2:
            if (login()) {
                loggedIn = 1;
                printf("Login successful! Welcome, %s\n", currentUser);
            } else {
                printf("Invalid username or password.\n");
            }
            break;
        case 3:
            viewSeats();

            return 0;
        default:
            printf("Invalid option. Try again.\n");
    }

    printf("\nPress Enter to continue...");
    getchar(); getchar(); // Pause and wait for user input
}

}

// Function Definitions

void registration() {
    FILE *fp;
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registration successful!\n");
}

int login() {
    FILE *fp;
    char username[50], password[50], fileUser[50], filePass[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("No registered users found.\n");
        return 0;
    }

    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            fclose(fp);
            strcpy(currentUser, username); // Store the logged-in user's name
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void viewSeats() {
    printf("Available seats:\n");
    for (int i = 1; i <= totalSeats; i++) {
        if (!seats[i - 1].isBooked) {
            printf("Seat %d is available\n", i);
        } else {
            printf("Seat %d is booked by %s\n", i, seats[i - 1].bookedBy);
        }
    }
}
