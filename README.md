# Contact Manager

A command-line contact manager written in C. Supports creating, viewing, editing, deleting, and searching contacts, with all data persisted to an external file so changes survive between sessions.

## Features

- Add new contacts (name and phone number)
- View all saved contacts
- Edit existing contacts
- Delete contacts
- Search by name
- Persistent storage via `contacts.txt`

## Project Structure
├── main.c         # Entry point and menu interface
├── operations.c   # Contact CRUD operations
├── operations.h   # Function declarations
└── contacts.txt   # Contact data file

## How to Compile and Run

```bash
gcc main.c operations.c -o contact_manager
./contact_manager
```

## Concepts Demonstrated

- Structs and pointers in C
- File I/O with `fopen`/`fread`/`fwrite`
- Modular design with separate header files
- String handling in C
