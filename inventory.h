#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int min_stock;
} Product;

void inventoryMenu();
void addProduct();
void viewProducts();
void editProduct();
void deleteProduct();

#endif
