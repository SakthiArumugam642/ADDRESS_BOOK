#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

/* Function definitions */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"

void print(const char *message, const char *color) {
    printf("%s%s\033[0m\n", color, message); // Print colored message and reset color
}

void print_success(const char *message) {
    print(message, GREEN);
}

void print_error(const char *message) {
    print(message, RED);
}

void print_prompt(const char *message) {
    print(message, YELLOW);
}

void print_box_header() {
    printf("+-----+---------------------------+-----------------+------------------------------+\n");
    printf("| ID  | Name                      | Mobile No       | Mail ID                      |\n");
    printf("+-----+---------------------------+-----------------+------------------------------+\n");
}

void print_box_footer() {
    printf("+-----+---------------------------+-----------------+------------------------------+\n");
}

int validate_name(char * name) {
    // char * name = addressbook->contact_details[addressbook->contact_count].Name;
    
    if (!isalpha(name[0])) {
    print_error("Error: Name should start with a letter ):");
    return 0;
    }

    if (isdigit(name[0]) || isspace(name[0])){
            print_error("Error: Name should not start with digit or space ):");
            return 0;
        } // Don't allow digit or space at start

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != ' '){
            print_error("Error: Name should contain only digits started after letters  ):");
            return 0;
        } // Only allow letters, digits, and space
    }

    return 1;
}

int validate_mob_no(char *no,struct Address_book * addressbook){
    // char * no = addressbook->contact_details[addressbook->contact_count].Mobile_number;

     if(no[0] < '6'){
            print_error("Error: Mob. No. should start with digit greater than 6 ):");
            return 0;
        }
    int i=0;
    if (strlen(no) != 10){
            print_error("Error: Mob. No. should have 10 digits ):");
            return 0;
        }
    while(no[i]){
      if(!isdigit(no[i])){
            print_error("Error: Mob. No. should not contain anything other than digits ):");
            return 0;
        }
        i++;
    }
    int j = 0;
    while(j<addressbook->contact_count){
    if(strcmp(no,addressbook->contact_details[j].Mobile_number)==0){
        print_error("Mob. no. was already present ):");
        return 0;
    }
    j++;
    }
    return 1;
}

int validate_mail(char *mail, struct Address_book *addressbook, int check_duplicate) {
    int len = strlen(mail);

    if (len < 4 || strcmp(&mail[len - 4], ".com") != 0)
     {
        print_error("Error: Mail should end with .com ):");
        return 0;
    }

    if (mail[len-1] == '.') {
        print_error("Error: Mail should not end with dot ):");
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (isupper(mail[i])) {
            print_error("Error: Mail should not have Capital letter ):");
            return 0;
        }
    }

    if (len < 6) {
        print_error("Error: Mail length is too short ):");
        return 0;
    }

    if (mail[0] == '.' || mail[0] == '@' || mail[0] == ' ') {
        print_error("Error: Mail should not start with dot/@/space ):");
        return 0;
    }

    char *at_ptr = strchr(mail, '@');
    if (at_ptr == NULL) {
        print_error("Error: Mail must have one @ ):");
        return 0;
    }

    if (*(at_ptr + 1) == '.') {
        print_error("Error: Mail should have domain after @  ):");
        return 0;
    }

    int local_len = at_ptr - mail;
    int domain_len = len - local_len - 1;

    if (local_len < 1 || domain_len < 3) {
        print_error("Error: Mail length is too short and have no domain ):");
        return 0;
    }

    // Check LOCAL PART (before @)
    for (int i = 0; i < local_len; i++) {
        char c = mail[i];
        if (!(isalnum(c) || c == '.' || c == '_')) {
            print_error("Error: Mail local part should contain only letters, digits, dot or underscore");
            return 0;
        }

        // No consecutive dots
        if (c == '.' && mail[i + 1] == '.') {
            print_error("Error: Mail should not have Consecutive dots ):");
            return 0;
        }
    }

    if (mail[local_len - 1] == '.') {
        print_error("Error: Mail should not end with dot before @ ):");
        return 0;
    }

    // Check for more than one '.com'
    int count = 0;
    int l = 0;
    while (mail[l]) {
        if (mail[l] == '.') {
            if (mail[l+1] == 'c' && mail[l+2] == 'o' && mail[l+3] == 'm') {
                count++;
            }
        }
        l++;
    }

    if (count >= 2) {
        print_error("Error: Mail should not have more than one dotcom ):");
        return 0;
    }

    // Check DOMAIN PART (after @)
    int dot_found = 0;
    for (int i = local_len + 1; i < len; i++) {
        char c = mail[i];
        if (!(isalpha(c) || c == '.')) {
            print_error("Error: Mail should not have digit after @ ):");
            return 0;
        }

        if (c == '.' && mail[i + 1] == '.') {
            print_error("Error: Mail should not have consecutive dots after @ ):");
            return 0;
        }

        if (c == '.') dot_found = 1;
    }

    if (!dot_found) {
        print_error("Error: Mail Must have at least one dot after @ ):");
        return 0;
    }

    // Duplicate check (only if enabled)
    if (check_duplicate && addressbook != NULL) {
        int j = 0;
        while (j < addressbook->contact_count) {
            if (strcmp(mail, addressbook->contact_details[j].Mail_ID) == 0) {
                print_error("Mail ID was already present ):");
                return 0;
            }
            j++;
        }
    }

    return 1;
}

int validate_mob(char *no){
    // char * no = addressbook->contact_details[addressbook->contact_count].Mobile_number;
    int i=0;
    
    if(no[0]<6){        
        print_error("Error: Mob. No. should start with digit greater than 6 ):");
            return 0;
        }
    if (strlen(no) != 10){
            print_error("Error: Mob. No. should have 10 digits ):");
            return 0;
        }
    while(no[i]){
      if(!isdigit(no[i])){
            print_error("Error: Mob. No. should not contain anything other than digits ):");
            return 0;
        }
        i++;
    }
    return 1;
}

int search_and_select_contact_by_name(struct Address_book *addressbook) {
    if (addressbook->contact_count == 0) {
        print_error("Error: Address Book is Empty ):");
        return -1;
    }

    char name[100];
    char choice_char;
    int indices[100];
    int match_count;

    while (1) {
        print_prompt("Enter the name: ");
        scanf(" %[^\n]", name);
        while (getchar() != '\n');

        if (!validate_name(name)) {
            print_error("Invalid name format");
            print_prompt("Do you want to retry? (Y/N): ");
            scanf(" %c", &choice_char);
            while (getchar() != '\n');
            if (choice_char == 'n' || choice_char == 'N') {
                print_error("Search cancelled");
                return -1;
            }
            continue;
        }

        match_count = 0;
        printf("Matches for '%s':\n", name);
        print_box_header();
        // printf("| %-3s | %-25s | %-15s | %-28s |\n","ID", "Name", "Mobile No", "Mail ID");

        for (int i = 0; i < addressbook->contact_count; i++) {
            if (strstr(addressbook->contact_details[i].Name, name)) {
                printf("| %-3d | %-25s | %-15s | %-28s |\n", match_count + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
                indices[match_count] = i;
                match_count++;
            }
        }
        print_box_footer();

        if (match_count == 0) {
            print_error("No contacts found with that name");
            print_prompt("Do you want to retry? (Y/N): ");
            scanf(" %c", &choice_char);
            while (getchar() != '\n');
            if (choice_char == 'n' || choice_char == 'N') {
                print_error("Search cancelled");
                return -1;
            }
            continue;
        }

        int choice;
        while (1) {
            print_prompt("Enter the ID of the contact you want to select: ");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                print_error("Invalid input. Please enter a number");
                continue;
            }
            while (getchar() != '\n');

            if (choice < 1 || choice > match_count) {
                print_error("Invalid choice. Please try again");
            } else {
                print_success("Contact selected successfully :)");
                return indices[choice - 1];
            }
        }
    }
}

int search_no(char *no, struct Address_book *addressbook) {
    char choice;

    while (1) {
        print_prompt("Enter Mobile Number: ");
        scanf("%[^\n]", no);
        while (getchar() != '\n');

        if (!validate_mob(no)) {
            print_error("Invalid mobile number format!");
            print_prompt("Do you want to retry? (Y/N): ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == 'n' || choice == 'N') {
                print_error("Search cancelled");
                return -1;
            }
            continue;
        }

        for (int j = 0; j < addressbook->contact_count; j++) {
            if (strcmp(no, addressbook->contact_details[j].Mobile_number) == 0) {
                print_success("Mobile number found");
                return j;
            }
        }

        print_error("Mobile number not found in Address Book");
        print_prompt("Do you want to retry? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        if (choice == 'n' || choice == 'N') {
            print_error("Search cancelled");
            return -1;
        }
    }
}

int search_mail(char *mail, struct Address_book *addressbook) {
    char choice;

    while (1) {
        print_prompt("Enter Mail ID: ");
        scanf("%[^\n]", mail);
        while (getchar() != '\n');

        if (!validate_mail(mail,NULL,0)) {
            print_error("Invalid email format!");
            print_prompt("Do you want to retry? (Y/N): ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == 'n' || choice == 'N') {
                print_error("Search cancelled");
                return -1;
            }
            continue;
        }

        for (int j = 0; j < addressbook->contact_count; j++) {
            if (strcmp(mail, addressbook->contact_details[j].Mail_ID) == 0) {
                print_success("Email ID found.");
                return j;
            }
        }

        print_error("Email ID not found in Address Book");
        print_prompt("Do you want to retry? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        if (choice == 'n' || choice == 'N') {
            print_error("Search cancelled");
            return -1;
        }
    }
}

void init_intitalization(struct Address_book *addressbook)
{
    FILE *fp = fopen("1.csv", "r");
    if (fp == NULL) {
        print_error("Error: Unable to open file for reading");
        return;
    }

    int count;
    if (fscanf(fp, "#%d\n", &count) != 1) {
        print_error("Error: Invalid file format");
        fclose(fp);
        return;
    }

    addressbook->contact_count = 0;

    for (int i = 0; i < count; i++) {
        char name[100], mobile[100], mail[100];

        if (fscanf(fp, "%99[^,],%99[^,],%99[^\n]\n", name, mobile, mail) != 3) {
            print_error("Error: Corrupted contact entry found");
            fclose(fp);
            return;
        }

        // Copy data into structure
        strcpy(addressbook->contact_details[addressbook->contact_count].Name, name);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number, mobile);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID, mail);

        addressbook->contact_count++;
    }

    fclose(fp);
    print_success("Contacts loaded successfully :)");

}

int create_contact(struct Address_book *addressbook)
{   
    char *name = addressbook->contact_details[addressbook->contact_count].Name;
    char *number = addressbook->contact_details[addressbook->contact_count].Mobile_number;
    char *mail = addressbook->contact_details[addressbook->contact_count].Mail_ID;

    while (1) {
        print_prompt("Enter the name of the contact: ");
        scanf(" %[^\n]", name);
        if (validate_name(name)) break;
        print_prompt("1. Retry\n2. Exit");
        int opt; scanf("%d", &opt);
        if (opt == 2) return 0;
    }

    while (1) {
        print_prompt("Enter the mobile number of the contact: ");
        scanf("%s", number);
        if (validate_mob_no(number,addressbook)) break;
        print_prompt("1. Retry\n2. Exit");
        int opt; scanf("%d", &opt);
        if (opt == 2) return 0;
    }

    while (1) {
        print_prompt("Enter the mail ID of the contact: ");
        scanf("%s", mail);
        if (validate_mail(mail,addressbook,1)) break;
        print_prompt("1. Retry\n2. Exit");
        int opt; scanf("%d", &opt);
        if (opt == 2) return 0;
    }

    addressbook->contact_count += 1;
    print_success("Contact saved successfully :)");
    return 0;
}

void list_contacts(struct Address_book *addressbook)
{
    printf("All Contact Details\n");
    print_box_header();
                
    for(int ind=0;ind<addressbook->contact_count;ind++){
        printf("| %-3d | %-25s | %-15s | %-28s |\n",ind+1,addressbook->contact_details[ind].Name,addressbook->contact_details[ind].Mobile_number,addressbook->contact_details[ind].Mail_ID);    }

        print_box_footer();
}

int search_contacts(struct Address_book *addressbook) {
    if (addressbook->contact_count == 0) {
        print_error("Address book is empty!");
        return 0;
    }

    int option;
    char choice;

    while (1) {
        print_prompt("| Search Contact menu :");
        print_prompt("1. Name");
        print_prompt("2. Mobile number");
        print_prompt("3. Mail ID");
        print_prompt("4. Exit");

        print_prompt("Enter the option: ");
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');  // clear input buffer
            print_error("Invalid input! Please enter a number between 1 and 4.");
            continue;
        }
        while (getchar() != '\n');  // flush newline

        if (option == 4) {
            print_success("Exited from search menu");
            return 0;
        }

        int index = -1;
        char input[100];

        switch (option) {
            case 1:
                index = search_and_select_contact_by_name(addressbook);
                break;

            case 2:
                index = search_no(input, addressbook);
                break;

            case 3:
                index = search_mail(input, addressbook);
                break;

            default:
                print_error("Invalid option! Please select from 1 to 4.");
                continue;
        }

        if (index != -1) {
            struct Contact_data *c = &addressbook->contact_details[index];
            print_success("Contact found:");
            print_box_header();
        printf("| %-3d | %-25s | %-15s | %-28s |\n",1,c->Name,c->Mobile_number,c->Mail_ID);

        print_box_footer();
        }

        print_prompt("Do you want to search again? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');

        if (choice == 'n' || choice == 'N') {
            print_success("Exited from search menu");
            break;
        }
    }
}

int edit_contact(struct Address_book *addressbook) {
    int search_opt;
    int ind = -1;
    char name[100], no[100], mail[100];

    print_prompt("Edit Contact Menu:");
    print_prompt("1. Search by Name\n2. Search by Mobile Number\n3. Search by Mail ID\nEnter option: ");
    scanf("%d", &search_opt);
    getchar();

    switch (search_opt) {
        case 1:
            ind = search_and_select_contact_by_name(addressbook);
            break;

        case 2:
            while (1) {
                print_prompt("Enter the mobile number: ");
                scanf("%s", no);

                if (!validate_mob(no)) {
                    print_error("Error: Invalid Mobile Number format ):");
                } else {
                    ind = search_no(no, addressbook);
                    if (ind == -1) {
                        print_error("Error: Contact not found ):");
                    } else break;
                }

                print_prompt("Do you want to retry? (Y/N): ");
                char retry;
                scanf(" %c", &retry);
                if (retry == 'N' || retry == 'n') return 0;
            }
            break;

        case 3:
            while (1) {
                print_prompt("Enter the mail ID: ");
                scanf("%s", mail);

                if (!validate_mail(mail, NULL, 0)) {
                    print_error("Error: Invalid Mail ID format ):");
                } else {
                    ind = search_mail(mail, addressbook);
                    if (ind == -1) {
                        print_error("Error: Contact not found ):");
                    } else break;
                }

                print_prompt("Do you want to retry? (Y/N): ");
                char retry;
                scanf(" %c", &retry);
                if (retry == 'N' || retry == 'n') return 0;
            }
            break;

        default:
            print_error("Error: Invalid option ):");
            return 0;
    }

    if (ind == -1) return 0;

    while (1) {
        printf("Editing Contact: %s\n", addressbook->contact_details[ind].Name);
        print_prompt("1. Name\n2. Mobile Number\n3. Mail ID\n4. All Details\n5. Exit\nEnter the option: ");
        int op;
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                while (1) {
                    print_prompt("Enter new name: ");
                    scanf(" %[^\n]", name);
                    if (!validate_name(name)) {
                        print_error("Error: Invalid Name ):");
                        print_prompt("1. Retry\n2. Cancel Edit");
                        int opt; scanf("%d", &opt);
                        if (opt == 2) break;
                    } else {
                        strcpy(addressbook->contact_details[ind].Name, name);
                        print_success("Contact updated successfully :)");
                        break;
                    }
                }
                break;

            case 2:
                while (1) {
                    print_prompt("Enter new mobile number: ");
                    scanf("%s", no);
                    if (!validate_mob_no(no, addressbook)) {
                        print_error("Error: Invalid Mobile Number ):");
                        print_prompt("1. Retry\n2. Cancel Edit");
                        int opt; scanf("%d", &opt);
                        if (opt == 2) break;
                    } else {
                        strcpy(addressbook->contact_details[ind].Mobile_number, no);
                        print_success("Contact updated successfully :)");
                        break;
                    }
                }
                break;

            case 3:
                while (1) {
                    print_prompt("Enter new mail ID: ");
                    scanf("%s", mail);
                    if (!validate_mail(mail, addressbook, 1)) {
                        print_error("Error: Invalid Mail ID ):");
                        print_prompt("1. Retry\n2. Cancel Edit");
                        int opt; scanf("%d", &opt);
                        if (opt == 2) break;
                    } else {
                        strcpy(addressbook->contact_details[ind].Mail_ID, mail);
                        print_success("Contact updated successfully :)");
                        break;
                    }
                }
                break;

            case 4:
                // Name
                while (1) {
                    print_prompt("Enter new name: ");
                    scanf(" %[^\n]", name);
                    if (validate_name(name)) {
                        strcpy(addressbook->contact_details[ind].Name, name);
                        break;
                    }
                    print_error("Error: Invalid Name ):");
                    print_prompt("1. Retry\n2. Cancel Edit");
                    int opt; scanf("%d", &opt);
                    if (opt == 2) return 0;
                }

                // Mobile Number
                while (1) {
                    print_prompt("Enter new mobile number: ");
                    scanf("%s", no);
                    if (validate_mob_no(no, addressbook)) {
                        strcpy(addressbook->contact_details[ind].Mobile_number, no);
                        break;
                    }
                    print_error("Error: Invalid Mobile Number ):");
                    print_prompt("1. Retry\n2. Cancel Edit");
                    int opt; scanf("%d", &opt);
                    if (opt == 2) return 0;
                }

                // Mail ID
                while (1) {
                    print_prompt("Enter new mail ID: ");
                    scanf("%s", mail);
                    if (validate_mail(mail, addressbook, 1)) {
                        strcpy(addressbook->contact_details[ind].Mail_ID, mail);
                        break;
                    }
                    print_error("Error: Invalid Mail ID ):");
                    print_prompt("1. Retry\n2. Cancel Edit");
                    int opt; scanf("%d", &opt);
                    if (opt == 2) return 0;
                }

                print_success("Contact updated successfully :)");
                break;

            case 5:
                return 0;

            default:
                print_error("Error: Invalid option ):");
        }
    }
}

int delete_contact(struct Address_book *addressbook) {
    int search_opt;
    int ind = -1;

    print_prompt("Delete Contact Menu:");
    print_prompt("1. Search by Name\n2. Search by Mobile Number\n3. Search by Mail ID\nEnter option: ");
    scanf("%d", &search_opt);
    getchar();

    switch (search_opt) {
        case 1:
            ind = search_and_select_contact_by_name(addressbook);
            break;

        case 2: {
            char no[100];
            while (1) {
                print_prompt("Enter the mobile number: ");
                scanf("%s", no);

                if (!validate_mob(no)) {
                    print_error("Error: Invalid Mobile Number format ):");
                } else {
                    ind = search_no(no, addressbook);
                    if (ind == -1) {
                        print_error("Error: Contact not found ):");
                    } else break;
                }

                print_prompt("Do you want to retry? (Y/N): ");
                char retry;
                scanf(" %c", &retry);
                if (retry == 'N' || retry == 'n') return 0;
            }
            break;
        }

        case 3: {
            char mail[100];
            while (1) {
                print_prompt("Enter the mail ID: ");
                scanf("%s", mail);

                if (!validate_mail(mail, NULL, 0)) {
                    print_error("Error: Invalid Mail ID format ):");
                } else {
                    ind = search_mail(mail, addressbook);
                    if (ind == -1) {
                        print_error("Error: Contact not found ):");
                    } else break;
                }

                print_prompt("Do you want to retry? (Y/N): ");
                char retry;
                scanf(" %c", &retry);
                if (retry == 'N' || retry == 'n') return 0;
            }
            break;
        }

        default:
            print_error("Error: Invalid option ):");
            return 0;
    }

    if (ind == -1) return 0;

    print_prompt("Deleting Contact:");
    printf("%-25s %-15s %-30s\n",
           addressbook->contact_details[ind].Name,
           addressbook->contact_details[ind].Mobile_number,
           addressbook->contact_details[ind].Mail_ID);

    print_prompt("Are you sure you want to delete this contact? (Y/N): ");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = ind; i < addressbook->contact_count - 1; i++) {
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];
        }
        addressbook->contact_count--;
        print_success("Contact deleted successfully :)");
    } else {
        print_prompt("Delete cancelled");
    }

    return 0;
}

int save_contacts(struct Address_book *addressbook)
{
    FILE * fp = fopen("1.csv","w");
    if (fp == NULL) {
        print_error("Error: Unable to open file for writing.");
        return -1;
    }
    fprintf(fp,"#%d\n",addressbook->contact_count);
    for(int ind = 0;ind<addressbook->contact_count;ind++){
    fprintf(fp,"%s,%s,%s\n",addressbook->contact_details[ind].Name,
           addressbook->contact_details[ind].Mobile_number,
           addressbook->contact_details[ind].Mail_ID);
    }
    fclose(fp);
    print_success("Contacts saved successfully :)");
    return 0;
} 
