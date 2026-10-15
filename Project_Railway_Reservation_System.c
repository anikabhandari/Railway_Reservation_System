#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passenger
{
    int pnr;
    char name[50];
    int age;
    char gender[10];
    char train[50];
    char source[30];
    char destination[30];
    int seatNo;

    struct Passenger *next;
};

struct WaitingPassenger
{
    char name[50];
    int age;
    char gender[10];
    char train[50];
    char source[30];
    char destination[30];

    struct WaitingPassenger *next;
};

struct Passenger *head = NULL;
struct WaitingPassenger *front = NULL;
struct WaitingPassenger *rear = NULL;
int pnrCounter = 1001;
int seatCounter = 1;

struct Passenger* createPassenger()
{
    struct Passenger *newPassenger;

    newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));

    printf("\nEnter Passenger Name: ");
    scanf(" %[^\n]", newPassenger->name);

    printf("Enter Age: ");
    scanf("%d", &newPassenger->age);

    printf("Enter Gender: ");
    scanf("%s", newPassenger->gender);

    printf("Enter Train Name: ");
    scanf(" %[^\n]", newPassenger->train);

    printf("Enter Source Station: ");
    scanf(" %[^\n]", newPassenger->source);

    printf("Enter Destination Station: ");
    scanf(" %[^\n]", newPassenger->destination);

    newPassenger->pnr = pnrCounter++;
    newPassenger->seatNo = seatCounter++;

    newPassenger->next = NULL;

    return newPassenger;
}

void bookTicket()
{
    struct Passenger *newPassenger;
    struct Passenger *temp;

    newPassenger = createPassenger();
    if (head == NULL)
    {
        head = newPassenger;
    }
    else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPassenger;
    }

    printf("\nTicket booked successfully!");
    printf("\nPNR Number : %d", newPassenger->pnr);
    printf("\nSeat Number: %d", newPassenger->seatNo);
}

void displayReservations() {
    struct Passenger *temp;
    if (head == NULL) {
        printf("\nNo confirmed reservations found.\n");
        return;
    }
    temp = head;

    printf("\nCONFIRMED RESERVATIONSn");
    while (temp != NULL)
    {
        printf("\nPNR Number     : %d", temp->pnr);
        printf("\nPassenger Name : %s", temp->name);
        printf("\nAge            : %d", temp->age);
        printf("\nGender         : %s", temp->gender);
        printf("\nTrain          : %s", temp->train);
        printf("\nSource         : %s", temp->source);
        printf("\nDestination    : %s", temp->destination);
        printf("\nSeat Number    : %d", temp->seatNo);
        temp = temp->next;
    }
}

void searchReservation() {
    struct Passenger *temp;
    int pnr;
    int found = 0;

    printf("\nEnter PNR Number to search: ");
    scanf("%d", &pnr);

    temp = head;

    while (temp != NULL)
    {
        if (temp->pnr == pnr)
        {
            printf("\nRESERVATION FOUND\n");
            printf("PNR Number     : %d\n", temp->pnr);
            printf("Passenger Name : %s\n", temp->name);
            printf("Age            : %d\n", temp->age);
            printf("Gender         : %s\n", temp->gender);
            printf("Train          : %s\n", temp->train);
            printf("Source         : %s\n", temp->source);
            printf("Destination    : %s\n", temp->destination);
            printf("Seat Number    : %d\n", temp->seatNo);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("\nReservation not found.\n");
    }
}

void addToWaitingList() {
    struct WaitingPassenger *newPassenger;
    newPassenger = (struct WaitingPassenger*)
                   malloc(sizeof(struct WaitingPassenger));

    printf("\nEnter Passenger Name: ");
    scanf(" %[^\n]", newPassenger->name);

    printf("Enter Age: ");
    scanf("%d", &newPassenger->age);

    printf("Enter Gender: ");
    scanf("%s", newPassenger->gender);

    printf("Enter Train Name: ");
    scanf(" %[^\n]", newPassenger->train);

    printf("Enter Source Station: ");
    scanf(" %[^\n]", newPassenger->source);

    printf("Enter Destination Station: ");
    scanf(" %[^\n]", newPassenger->destination);

    newPassenger->next = NULL;
    if (rear == NULL) {
        front = rear = newPassenger;
    }
    else {
        rear->next = newPassenger;
        rear = newPassenger;
    }
    printf("\nPassenger added to waiting list successfully.\n");
}

void displayWaitingList() {
    struct WaitingPassenger *temp;
    if (front == NULL) {
        printf("\nWaiting list is empty.\n");
        return;
    }
    temp = front;
    printf("\nWAITING LISTn");
    while (temp != NULL) {
        printf("\nPassenger Name : %s", temp->name);
        printf("\nAge            : %d", temp->age);
        printf("\nGender         : %s", temp->gender);
        printf("\nTrain          : %s", temp->train);
        printf("\nSource         : %s", temp->source);
        printf("\nDestination    : %s", temp->destination);
        temp = temp->next;
    }
}

void cancelTicket() {
    struct Passenger *temp;
    struct Passenger *previous;
    int pnr;
    printf("\nEnter PNR Number to cancel: ");
    scanf("%d", &pnr);
    temp = head;
    previous = NULL;

    while (temp != NULL) {
        if (temp->pnr == pnr) {
            /* If first reservation is cancelled */
            if (previous == NULL) {
                head = temp->next;
            }
            else {
                previous->next = temp->next;
            }
            printf("\nTicket cancelled successfully.");
            printf("\nPassenger Name: %s", temp->name);
            printf("\nPNR Number: %d\n", temp->pnr);
            free(temp);

            if (front != NULL) {
                struct WaitingPassenger *waiting;
                struct Passenger *newPassenger;
                struct Passenger *last;
                waiting = front;
                newPassenger = (struct Passenger*)
                                malloc(sizeof(struct Passenger));

                strcpy(newPassenger->name, waiting->name);
                newPassenger->age = waiting->age;
                strcpy(newPassenger->gender, waiting->gender);
                strcpy(newPassenger->train, waiting->train);
                strcpy(newPassenger->source, waiting->source);
                strcpy(newPassenger->destination, waiting->destination);

                newPassenger->pnr = pnrCounter++;
                newPassenger->seatNo = seatCounter++;
                newPassenger->next = NULL;

                front = front->next;
                if (front == NULL) {
                    rear = NULL;
                }

                free(waiting);
                if (head == NULL) {
                    head = newPassenger;
                }
                else {
                    last = head;
                    while (last->next != NULL) {
                        last = last->next;
                    }
                    last->next = newPassenger;
                }

                printf("\nPassenger from waiting list has been confirmed!");
                printf("\nNew PNR Number : %d", newPassenger->pnr);
                printf("\nNew Seat Number: %d\n", newPassenger->seatNo);
            }
            return;
        }
        previous = temp;
        temp = temp->next;
    }
    printf("\nPNR Number not found.\n");
}

int main() {
    int choice;
    do
    {
        printf("\nRAILWAY RESERVATION SYSTEM");
        printf("\n1. Book Ticket");
        printf("\n2. Display Reservations");
        printf("\n3. Search Reservation");
        printf("\n4. Cancel Ticket");
        printf("\n5. Add Passenger to Waiting List");
        printf("\n6. Display Waiting List");
        printf("\n7. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket();
                break;

            case 2:
                displayReservations();
                break;

            case 3:
                searchReservation();
                break;

            case 4:
                cancelTicket();
                break;

            case 5:
                addToWaitingList();
                break;

            case 6:
                displayWaitingList();
                break;

            case 7:
                printf("\nThank you for using Railway Reservation System!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 7);
    return 0;
}
