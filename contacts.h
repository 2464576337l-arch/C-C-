#ifndef CONTACTS_H
#define CONTACTS_H

typedef struct Contact
{
   char name[50];
   char phone[20];
}Contact;

void addContact(Contact *list, int *count);
void saveToFile(Contact *list, int *count, const char *filename);   
Contact* loadFromFile( int *count, const char *filename);
void deleteContact(Contact *list, int *count, const char *name);    

#endif // CONTACTS_H
