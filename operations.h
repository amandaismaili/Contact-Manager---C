#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef struct {
    char person[31];
    char phone_number[16];
}Contact;

void save_contact(Contact contact);
void clean_buffer();
void add_contact();
void search_contact();
void delete_contact();
void display_all();
void edit_contact();
#endif