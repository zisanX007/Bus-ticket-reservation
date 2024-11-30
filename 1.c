#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int seatNumber;
    int isBooked;
    char bookedBy[50];
} Seat;

Seat seats[20];
int totalSeats = 20;

void registration();
int login();
void viewSeats();
void bookTicket(char username[]);
void payment(char username[], int seatNumber);
void displayBookingDetails(char username[]);
void exitProgram();

int main() {
    int choice;
    char username[50];

    printf("Welcome to the Bus Ticket Reservation System!\n");

    while (1) {
        printf("\n1. Register\n2. Login\n3. View Available Seats\n4. Book Ticket\n5. Payment\n6. Display Booking Details\n7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registration();
                break;
            case 2:
                if (login()) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                viewSeats();
                break;
            case 4:
                printf("Enter your username: ");
                scanf("%s", username);
                bookTicket(username);
                break;
            case 5:
                printf("Enter your username: ");
                scanf("%s", username);
                int seatNumber;
                printf("Enter seat number: ");
                scanf("%d", &seatNumber);
                payment(username, seatNumber);
                break;
            case 6:
                printf("Enter your username: ");
                scanf("%s", username);
                displayBookingDetails(username);
                break;
            case 7:
                exitProgram();
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

void registration() {
    FILE *fp;
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
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
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void viewSeats() {
    for (int i = 1; i <= totalSeats; i++) {
        if (!seats[i - 1].isBooked) {
            printf("Seat %d is available\n", i);
        } else {
            printf("Seat %d is booked by %s\n", i, seats[i - 1].bookedBy);
        }
    }
}

void bookTicket(char username[]) {
    int seatNumber;
    FILE *fp;

    printf("Enter seat number to book (1-%d): ", totalSeats);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > totalSeats) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNumber - 1].isBooked) {
        printf("Seat is already booked.\n");
    } else {
        seats[seatNumber - 1].isBooked = 1;
        strcpy(seats[seatNumber - 1].bookedBy, username);

        fp = fopen("bookings.txt", "a");
        if (fp == NULL) {
            return;
        }

        fprintf(fp, "Seat %d booked by %s\n", seatNumber, username);
        fclose(fp);

        printf("Seat %d booked successfully!\n", seatNumber);
    }
}

void payment(char username[], int seatNumber) {
    FILE *fp;

    if (seatNumber < 1 || seatNumber > totalSeats || !seats[seatNumber - 1].isBooked || strcmp(seats[seatNumber - 1].bookedBy, username) != 0) {
        printf("Invalid seat or booking details.\n");
        return;
    }

    fp = fopen("payments.txt", "a");
    if (fp == NULL) {
        printf("Error processing payment.\n");
        return;
    }

    fprintf(fp, "User: %s | Seat: %d | Status: Paid\n", username, seatNumber);
    fclose(fp);

    printf("Payment successful for Seat %d by %s!\n", seatNumber, username);
}

void displayBookingDetails(char username[]) {
    int found = 0;

    for (int i = 0; i < totalSeats; i++) {
        if (seats[i].isBooked && strcmp(seats[i].bookedBy, username) == 0) {
            printf("Seat %d\n", i + 1);
            found = 1;
        }
    }

    if (!found) {
        printf("No bookings found.\n");
    }
}

void exitProgram() {
    printf("Thank you for using the Bus Ticket Reservation System. Goodbye!\n");
}

