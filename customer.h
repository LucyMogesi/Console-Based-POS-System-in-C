#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int id;
    char name[50];
    char phone[20];
} Customer;

void customerMenu();
void addCustomer();
void viewCustomers();
void editCustomer();
void deleteCustomer();

#endif
