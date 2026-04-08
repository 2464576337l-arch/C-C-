#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"

void addContact(Contact *list, int *count){
    if (*count >= 100) {
        printf("Contact list is full.\n");
        return;
    }
    
    printf("Enter name: ");
    fgets(list[*count].name, sizeof(list[*count].name), stdin);
    list[*count].name[strcspn(list[*count].name, "\n")] = '\0'; // Remove newline character
    
    printf("Enter phone number: ");
    fgets(list[*count].phone, sizeof(list[*count].phone), stdin);
    list[*count].phone[strcspn(list[*count].phone, "\n")] = '\0'; // Remove newline character
    
    (*count)++;
    printf("Contact added successfully.Now you have %d contacts.\n", *count);
}

void saveToFile(Contact *list, int *count, const char *filename){
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    fwrite(count, sizeof(int), 1, file); // Write the count of contacts first
    fwrite(list, sizeof(Contact), *count, file); // Write the contact list
    
    fclose(file);
    printf("Contacts saved to file successfully.\n");
}

Contact* loadFromFile( int *count, const char *filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing contact file found. Starting with an empty contact list.\n");
        *count = 0; // No contacts loaded
        return NULL; // Return NULL to indicate no contacts loaded  
    }
    
    fread(count, sizeof(int), 1, file); // Read the count of contacts first
    Contact *list = malloc(sizeof(Contact) * (*count)); // Allocate memory for contacts
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL; // Memory allocation failed, return NULL
    }
    fread(list, sizeof(Contact), *count, file);
    printf("\n%-20s | %-20s\n", "Name", "Phone");
    printf("---------------------|-------------------\n");
    for (size_t i = 0; i < *count; i++)
    {
        printf("%-20s | %-20s\n", list[i].name, list[i].phone);
    }
    printf("---------------------|-------------------\n");
    fclose(file);
    printf("Contacts loaded from file successfully. You have %d contacts.\n", *count);
    return list; // Return the loaded contact list
}

void deleteContact(Contact *list, int *count, const char *name){
    for (int i = 0; i < *count; i++) {
        if (strcmp(list[i].name, name) == 0) {
            // Shift remaining contacts left
            for (int j = i; j < *count - 1; j++) {
                list[j] = list[j + 1];
            }
            (*count)--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}