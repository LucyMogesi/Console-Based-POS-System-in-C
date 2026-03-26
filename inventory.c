#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define INVENTORY_FILE "inventory.csv"

void inventoryMenu() {
    int choice;
    do {
        printf("\n--- Inventory Menu ---\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Edit Product\n");
        printf("4. Delete Product\n");
        printf("0. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: editProduct(); break;
            case 4: deleteProduct(); break;
            case 0: break;
            default: printf("Invalid option!\n");
        }
    } while(choice != 0);
}

void addProduct() {
    int file_exists = 0;
    FILE *check = fopen(INVENTORY_FILE, "r");
    if (check != NULL) {
        file_exists = 1;
        fclose(check);
    }

    FILE *fp = fopen(INVENTORY_FILE, "a+");
    if (fp == NULL) {
        printf("Error opening inventory file!\n");
        return;
    }

    // Write header if file is new
    if (!file_exists) {
        fprintf(fp, "code,name,price,quantity,min_stock\n");
    }

    Product p;
    printf("Enter product code: ");
    scanf("%d", &p.id);
    printf("Enter product name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter product price: ");
    scanf("%f", &p.price);
    printf("Enter quantity: ");
    scanf("%d", &p.quantity);
    printf("Enter minimum stock: ");
    scanf("%d", &p.min_stock);

    rewind(fp);
    char line[200];
    Product temp;

    fgets(line, sizeof(line), fp); // Skip header line
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%d,%d", &temp.id, temp.name, &temp.price, &temp.quantity, &temp.min_stock);
        if (temp.id == p.id || strcmp(temp.name, p.name) == 0) {
            printf("Error: Product code or name already exists!\n");
            fclose(fp);
            return;
        }
    }

    fprintf(fp, "%d,%s,%.2f,%d,%d\n", p.id, p.name, p.price, p.quantity, p.min_stock);
    fclose(fp);

    printf("Product added successfully!\n");
}


void viewProducts() {
    FILE *fp = fopen(INVENTORY_FILE, "r");
    if (fp == NULL) {
        printf("No inventory found.\n");
        return;
    }

    Product p;
    char line[200];

    printf("\n%-5s %-20s %-10s %-10s %-10s\n", "ID", "Name", "Price", "Qty", "Min");
    printf("-----------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%d,%d", &p.id, p.name, &p.price, &p.quantity, &p.min_stock);
        printf("%-5d %-20s %-10.2f %-10d %-10d", p.id, p.name, p.price, p.quantity, p.min_stock);
        if (p.quantity <= p.min_stock) {
            printf("  <-- LOW STOCK!");
        }
        printf("\n");
    }

    fclose(fp);
}

void editProduct() {
    FILE *fp = fopen(INVENTORY_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int id, found = 0;
    printf("Enter product ID to edit: ");
    scanf("%d", &id);

    char line[200];
    Product p;

    fgets(line, sizeof(line), fp);  // skip original header
    fprintf(temp, "code,name,price,quantity,min_stock\n");  // write header to new file

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%d,%d", &p.id, p.name, &p.price, &p.quantity, &p.min_stock);

        if (p.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]", p.name);
            printf("Enter new price: ");
            scanf("%f", &p.price);
            printf("Enter new quantity: ");
            scanf("%d", &p.quantity);
            printf("Enter new min stock: ");
            scanf("%d", &p.min_stock);
        }

        fprintf(temp, "%d,%s,%.2f,%d,%d\n", p.id, p.name, p.price, p.quantity, p.min_stock);
    }

    fclose(fp);
    fclose(temp);
    remove(INVENTORY_FILE);
    rename("temp.csv", INVENTORY_FILE);

    if (found)
        printf("Product updated.\n");
    else
        printf("Product ID not found.\n");
}

void deleteProduct() {
    FILE *fp = fopen(INVENTORY_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int id, found = 0;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    char line[200];
    Product p;

    // ✅ Skip and rewrite header
    fgets(line, sizeof(line), fp); // Skip original header
    fprintf(temp, "code,name,price,quantity,min_stock\n"); // Write header to new file

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%d,%d", &p.id, p.name, &p.price, &p.quantity, &p.min_stock);

        if (p.id == id) {
            found = 1;
            continue; // Skip this product (delete it)
        }

        fprintf(temp, "%d,%s,%.2f,%d,%d\n", p.id, p.name, p.price, p.quantity, p.min_stock);
    }

    fclose(fp);
    fclose(temp);
    remove(INVENTORY_FILE);
    rename("temp.csv", INVENTORY_FILE);

    if (found)
        printf("Product deleted successfully.\n");
    else
        printf("Product not found.\n");
}

