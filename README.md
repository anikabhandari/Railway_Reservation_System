# Railway Reservation System

A console-based Railway Reservation System developed in C to manage passenger bookings, ticket cancellations, reservation searches, and waiting lists.

## Features
- Book and display confirmed tickets.
- Search and cancel reservations using PNR numbers.
- Manage a waiting list using a queue.
- Automatically confirm waiting-list passengers when a ticket is cancelled.

## Concepts Used
- C Programming
- Structures and Pointers
- Singly Linked Lists
- Queues (FIFO)
- Dynamic Memory Allocation

## How to Run

Compile the program using GCC:

```bash
gcc railway_reservation.c -o railway_reservation
```

Run the executable:

```bash
./railway_reservation
```

On Windows, run `railway_reservation.exe`.

## Note
Passenger records are stored in memory and are not permanently saved after the program exits.

## Project Type
Academic Project | Data Structures and Algorithms (DSA)
