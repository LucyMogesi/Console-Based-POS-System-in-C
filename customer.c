#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

#define CUSTOMER_FILE "customers.csv"

void customerMenu() {
    int choice;
    do {
        printf("\n--- Customer Menu ---\n");
        printf("1. Add Customer\n");
        printf("2. View Customers\n");
        printf("3. Edit Customer\n");
        printf("4. Delete Customer\n");
        printf("0. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: editCustomer(); break;
            case 4: deleteCustomer(); break;
            case 0: break;
            default: printf("Invalid option!\n");
        }
    } while(choice != 0);
}

void addCustomer() {
    int file_exists = 0;
    FILE *check = fopen(CUSTOMER_FILE, "r");
    if (check != NULL) {
        file_exists = 1;
        fclose(check);
    }

    FILE *fp = fopen(CUSTOMER_FILE, "a+");
    if (fp == NULL) {
        printf("Error opening customer file!\n");
        return;
    }
    if (!file_exists) {
        fprintf(fp, "id,name,phone\n");
    }

    Customer c;
    printf("Enter customer ID: ");
    scanf("%d", &c.id);
    printf("Enter customer name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone number: ");
    scanf(" %[^\n]", c.phone);

    rewind(fp);
    char line[150];
    Customer temp;

    fgets(line, sizeof(line), fp);  // skip header
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%s", &temp.id, temp.name, temp.phone);
        if (temp.id == c.id || strcmp(temp.phone, c.phone) == 0) {
            printf("Customer ID or phone already exists!\n");
            fclose(fp);
            return;
        }
    }

    fprintf(fp, "%d,%s,%s\n", c.id, c.name, c.phone);
    fclose(fp);
    printf("Customer added successfully!\n");
}


void viewCustomers() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL) {
        printf("No customer data found.\n");
        return;
    }

    char line[150];
    Customer c;

    printf("\n%-5s %-20s %-15s\n", "ID", "Name", "Phone");
    printf("-----------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%s", &c.id, c.name, c.phone);
        printf("%-5d %-20s %-15s\n", c.id, c.name, c.phone);
    }

    fclose(fp);
}

void editCustomer() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int id, found = 0;
    printf("Enter customer ID to edit: ");
    scanf("%d", &id);

    char line[150];
    Customer c;

    // ✅ Skip and rewrite header
    fgets(line, sizeof(line), fp); // skip header in original
    fprintf(temp, "id,name,phone\n"); // write header in temp

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%s", &c.id, c.name, c.phone);

        if (c.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]", c.name);
            printf("Enter new phone: ");
            scanf(" %[^\n]", c.phone);
        }

        fprintf(temp, "%d,%s,%s\n", c.id, c.name, c.phone);
    }

    fclose(fp);
    fclose(temp);
    remove(CUSTOMER_FILE);
    rename("temp.csv", CUSTOMER_FILE);

    if (found)
        printf("Customer updated successfully.\n");
    else
        printf("Customer ID not found.\n");
}

void deleteCustomer() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int id, found = 0;
    printf("Enter customer ID to delete: ");
    scanf("%d", &id);

    char line[150];
    Customer c;

    // ✅ Skip and rewrite header
    fgets(line, sizeof(line), fp); // skip original header
    fprintf(temp, "id,name,phone\n"); // write to new file

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%s", &c.id, c.name, c.phone);

        if (c.id == id) {
            found = 1;
            continue; // delete this record
        }

        fprintf(temp, "%d,%s,%s\n", c.id, c.name, c.phone);
    }

    fclose(fp);
    fclose(temp);
    remove(CUSTOMER_FILE);
    rename("temp.csv", CUSTOMER_FILE);

    if (found)
        printf("Customer deleted successfully.\n");
    else
        printf("Customer not found.\n");
}
