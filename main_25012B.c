#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    char option;
    struct Address_book addressbook;
    
    addressbook.contact_count = 0;
    init_intitalization(&addressbook);


    while (1)
    {
        print_prompt("\nAddress book menu\n"); /* Give a prompt message for a user */
        print_prompt("1.Add contact\n2.Edit contact\n3.Delete contact\n4.search contact\n5.Display contact\n6.Save contact\n7.Exit\n");
        print_prompt("Enter the option : ");
        scanf("%hhd", &option);

        switch (option) /* Based on choosed option */
        {
            case 1:
            {
                create_contact(&addressbook);
                break;
            }

            case 2:
            {
                // printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
                edit_contact(&addressbook);
                break;
            }
            case 3:
                print_prompt("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
                delete_contact(&addressbook);
                break;

            case 4:
            {
                 /* Providing menu */
                search_contacts(&addressbook);
                break;
            }
            case 5:
            {
                // printf("List contacts:");
                list_contacts(&addressbook);
                break;
            }

            case 6:
                print_prompt("Saving contacts\n");
                save_contacts(&addressbook);
                break;

            case 7:
                print_prompt("INFO : Save and Exit...\n");
                return 0;
                break;

            default:
                print_prompt("Invalid option \n");
                break;
            }
    }
    return 0;
}
