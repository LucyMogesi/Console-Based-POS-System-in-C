#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "customer.h"
#include "sales.h"

void clearScreen() {
    system("cls");  // Windows-only clear screen
}

int main() {
    int choice;

    // ✅ LOGIN SECTION START
    char username[30], password[30];

    printf("=== LOGIN ===\n");
    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "1234") != 0) {
        printf("Access denied!\n");
        return 1;
    }
    // ✅ LOGIN SECTION END

    do {
        clearScreen();
        printf("=====================================\n");
        printf("      POINT OF SALE SYSTEM - C       \n");
        printf("=====================================\n");
        printf("1. Inventory Management\n");
        printf("2. Customer Management\n");
        printf("3. Sales / New Transaction\n");
        printf("0. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: inventoryMenu(); break;
            case 2: customerMenu(); break;
            case 3: salesMenu(); break;
            case 0: printf("Exiting system...\n"); break;
            default: printf("Invalid option. Try again.\n"); break;
        }

        if (choice != 0) {
            printf("\nPress Enter to return to main menu...");
            getchar(); getchar(); // pause
        }

    } while(choice != 0);

    return 0;
}
