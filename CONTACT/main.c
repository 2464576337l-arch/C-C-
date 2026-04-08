#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"

int main() {
    int total = 0;           // 当前人数
    int choice;

    // 程序启动先尝试加载数据
    Contact *myContacts = loadFromFile( &total, "data.bin");

    if(myContacts == NULL) {
        myContacts = malloc(sizeof(Contact) * 100); // 分配内存
        if (myContacts == NULL) {
            printf("Memory allocation failed.\n");
            return 1; // 内存分配失败，退出程序
        }
    }

    while(1) {
        printf("\n--contacts--\n");
        printf("1. add contact\n2. save and exit\n3. delete contact\nchoice: ");
        scanf("%d", &choice);
        getchar(); // 清理 scanf 留下的回车符

        if (choice == 1) {
            addContact(myContacts, &total);
        } else if (choice == 2) {
            saveToFile(myContacts, &total, "data.bin");
            break; 
        } else if (choice == 3) {
            char name[50];
            printf("Enter the name of the contact to delete: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove newline character
            deleteContact(myContacts, &total, name);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    free(myContacts); // 释放内存
    printf("Contacts saved and program exited.\n");
    return 0;
}