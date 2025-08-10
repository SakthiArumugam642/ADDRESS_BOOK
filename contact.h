#ifndef CONTACT_H
#define CONTACT_H

struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
};


struct Address_book
{
    struct Contact_data contact_details[100];
    int contact_count;
};

/* Function declarations */
int validate_name(char *);
void print(const char *, const char *);
void print_success(const char *message);
void print_error(const char *message);
void print_prompt(const char *message);
int validate_mob_no(char *,struct Address_book *);
int validate_mob(char *);
int validate_mail(char *,struct Address_book*,int);
int search_name(char *,struct Address_book *);
int search_no(char *,struct Address_book *);
int search_mail(char *,struct Address_book *);
void init_intitalization(struct Address_book *addressbook);
int create_contact(struct Address_book *);
void list_contacts(struct Address_book *);
int search_contacts(struct Address_book *addressbook);
int edit_contact(struct Address_book *addressbook);
int delete_contact(struct Address_book *addressbook);
int save_contacts(struct Address_book *addressbook);

#endif // CONTACT_H
// CONTACT_H        