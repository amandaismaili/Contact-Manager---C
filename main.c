#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main(void){
    printf("Welcome to The Contact Manager System\n");
    while(1){
        printf("1. Add contact\n2. Search for a contact\n3. Delete a contact\n4. View all contacts\n5. Edit a contact\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clean_buffer();

        if (choice < 1 || choice > 5){
            printf("Invalid choice.\n");
            continue;
        }

        if(choice == 1 ) add_contact();
        else if (choice == 2) search_contact();
        else if (choice == 3) delete_contact();
        else if(choice == 4) display_all();
        else if(choice == 5) edit_contact();

        char again;
        printf("Do you wish to go again?(y/n): ");
        scanf(" %c", &again);
        clean_buffer();

        if(again != 'y') break;
    }

    return 0;
}
