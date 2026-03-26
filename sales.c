#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sales.h"
#include "inventory.h"
#include "customer.h"

#define CUSTOMER_FILE "customers.csv"
#define INVENTORY_FILE "inventory.csv"

void salesMenu() {
    FILE *custFp = fopen(CUSTOMER_FILE, "r");
    if (custFp == NULL) {
        printf("Customer file not found.\n");
        return;
    }

    int custId, found = 0;
    Customer cust;
    char line[200];

    printf("Enter customer ID: ");
    scanf("%d", &custId);

    fgets(line, sizeof(line), custFp); // Skip header
    while (fgets(line, sizeof(line), custFp)) {
        sscanf(line, "%d,%[^,],%s", &cust.id, cust.name, cust.phone);
        if (cust.id == custId) {
            found = 1;
            break;
        }
    }
    fclose(custFp);

    if (!found) {
        printf("Customer not found.\n");
        return;
    }

    char cashier[50];
    printf("Enter cashier name: ");
    scanf(" %[^\n]", cashier);

    // Create receipt file
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char filename[64], datetime[64];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", t);
    sprintf(filename, "receipt_%d%02d%02d%02d%02d.txt",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min);

    FILE *receipt = fopen(filename, "w");
    if (!receipt) {
        printf("Failed to create receipt file.\n");
        return;
    }

    fprintf(receipt, "=========================================\n");
    fprintf(receipt, "           POINT OF SALE RECEIPT         \n");
    fprintf(receipt, "=========================================\n");
    fprintf(receipt, "Date: %s\n", datetime);
    fprintf(receipt, "Customer: %s\nPhone: %s\nCashier: %s\n", cust.name, cust.phone, cashier);
    fprintf(receipt, "-----------------------------------------\n");
    fprintf(receipt, "%-5s %-15s %-6s %-8s %-10s\n", "ID", "Product", "Qty", "Price", "Subtotal");

    float total = 0.0;
    int total_items = 0;
    char more = 'y';

    while (more == 'y' || more == 'Y') {
        int prodId, qty, prodFound = 0;
        printf("Enter product ID: ");
        scanf("%d", &prodId);
        printf("Enter quantity: ");
        scanf("%d", &qty);

        FILE *invFp = fopen(INVENTORY_FILE, "r");
        FILE *temp = fopen("temp.csv", "w");
        if (invFp == NULL || temp == NULL) {
            printf("Error opening inventory files.\n");
            return;
        }

        Product p;
        char line[256];

        fgets(line, sizeof(line), invFp); // Skip header
        fprintf(temp, "code,name,price,quantity,min_stock\n"); // Write header

        while (fgets(line, sizeof(line), invFp)) {
            sscanf(line, "%d,%[^,],%f,%d,%d", &p.id, p.name, &p.price, &p.quantity, &p.min_stock);

            if (p.id == prodId) {
                prodFound = 1;
                if (p.quantity < qty) {
                    printf("Not enough stock! Available: %d\n", p.quantity);
                } else {
                    float subtotal = qty * p.price;
                    total += subtotal;
                    total_items += qty;
                    p.quantity -= qty;

                    fprintf(receipt, "%-5d %-15s %-6d %-8.2f %-10.2f\n",
                            p.id, p.name, qty, p.price, subtotal);
                }
            }

            // Write product line (possibly updated) back
            fprintf(temp, "%d,%s,%.2f,%d,%d\n", p.id, p.name, p.price, p.quantity, p.min_stock);
        }

        fclose(invFp);
        fclose(temp);
        remove(INVENTORY_FILE);
        rename("temp.csv", INVENTORY_FILE);

        if (!prodFound) {
            printf("Product not found.\n");
        }

        printf("Add another product? (y/n): ");
        scanf(" %c", &more);
    }

    fprintf(receipt, "-----------------------------------------\n");
    fprintf(receipt, "TOTAL ITEMS: %d\n", total_items);
    fprintf(receipt, "TOTAL: %.2f\n", total);
    fprintf(receipt, "=========================================\n");
    fprintf(receipt, "         THANK YOU FOR SHOPPING!         \n");
    fprintf(receipt, "=========================================\n");

    fclose(receipt);
    printf("Transaction complete. Receipt saved to %s\n", filename);
}
