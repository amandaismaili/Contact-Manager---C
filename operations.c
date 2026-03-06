#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

void save_contact(Contact contact){
    FILE *pF = fopen("contacts.txt", "a");

    if (!pF){
        printf("Error opening this file.");
        return;
    }

    if (fprintf(pF, "%s: %s\n", contact.person, contact.phone_number) < 0) 
        printf("Write failed!\n");

    fclose(pF);
}


void clean_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void add_contact(void){
    Contact contact;
    printf("To add a contact enter the name and phone number.\n");

    printf("Name: ");
    fgets(contact.person, 31, stdin);
    contact.person[strcspn(contact.person, "\n")] = 0;
 
    printf("Number: ");
    fgets(contact.phone_number, 16, stdin);
    contact.phone_number[strcspn(contact.phone_number, "\n")] = 0;

    save_contact(contact);
    printf("Contact saved successfully.\n");
}

void search_contact(){
    FILE *pF = fopen("contacts.txt", "r");
    if(!pF){
        printf("Error opening the file.\n");
        return;
    }

    char line[200];    
    char name[30];
    int found = 0;

    printf("To search for someone, enter their name.\n");
    printf("Name: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;

    while (fgets(line, sizeof(line), pF)) {
        char temp[200];
        strcpy(temp, line);  

        char *copy = strtok(temp, ":");
        if(copy && strcmp(copy, name) == 0){
            printf("%s", line);
            found = 1;
            break;
        }
    }

    if(!found) printf("Contact not found.\n");
    fclose(pF);
}

void delete_contact(){
    FILE *pF = fopen("contacts.txt", "r");
    if(!pF){
        printf("Error opening this file.\n");
        return;
    }

    FILE *tempf = fopen("temporary.txt", "w");
    if(!tempf){
        printf("Error creating temporary file.\n");
        fclose(pF);
        return;
    }

    char line[200];    
    char name[30];
    int found = 0;

    printf("To search for someone, enter their name.\n");
    printf("Name: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;

    while(fgets(line, sizeof(line), pF)){
        char copy[200];
        strcpy(copy, line);

        char *token = strtok(copy, ":");

        if(token && strcmp(token, name) == 0){
            found = 1;
        }   
        else {
            fprintf(tempf, "%s", line);
        }     
    }      
    
    fclose(pF);
    fclose(tempf);

    if(found){
        remove("contacts.txt");
        rename("temporary.txt", "contacts.txt");
        printf("Contact deleted successfully.\n");
    } else {
        remove("temporary.txt");
        printf("Contact not found.\n");
    }
}

void display_all(){
    FILE *pF = fopen("contacts.txt", "r");
    if(!pF){
        printf("Error reading this file.\n");
        return;
    }

    char line[200];
    int found = 0;

    printf("-------Your Contacts--------\n");
    while(fgets(line, 200, pF) != NULL){
        printf("%s", line);
        found = 1;
    }

    if(!found) printf("No contacts saved yet.\n");

    fclose(pF);
}

void edit_contact(){
    FILE *pF = fopen("contacts.txt", "r");
    if(!pF){
        printf("Error opening this file.\n");
        return;
    }

    FILE *pFt = fopen("temporary.txt", "w");
    if(!pFt){
        printf("Cannot open temporary file.\n");
        fclose(pF);
        return;
    }

    char line[200];
    char name[30];
    char change_category[10];
    char new[30];
    int found = 0;

    printf("Enter contact name to edit: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Do you wish to change name or number(name/num): ");
    fgets(change_category, 10, stdin);
    change_category[strcspn(change_category, "\n")] = 0;

    printf("Enter new name or number: ");
    fgets(new, 30, stdin);
    new[strcspn(new, "\n")] = 0;

    while(fgets(line, sizeof(line), pF)){
        char copy[200];
        strcpy(copy, line);

        char *old_name = strtok(copy, ":");
        char *old_number = strtok(NULL, "\n");

        if(old_name && strcmp(name, old_name) == 0){
            found = 1;

            if (strcmp(change_category, "name") == 0){
                fprintf(pFt, "%s: %s\n", new, old_number);

            } else if (strcmp(change_category, "num") == 0){
                fprintf(pFt, "%s: %s\n", old_name, new);

            } else {
                fprintf(pFt, "%s", line);
            }
        } else {
            fprintf(pFt, "%s", line);
        }
    }
    fclose(pF);
    fclose(pFt);
    
    if(found){
        remove("contacts.txt");
        rename("temporary.txt", "contacts.txt");
        printf("Contact updated successfully.\n");
    } else {
        remove("temporary.txt");
        printf("Contact not found.\n");
    }
}