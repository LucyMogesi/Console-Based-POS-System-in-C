
1. Title & Objective

# Title:
# “Building a Console-Based POS System in C – A Beginner’s Guide”

# Technology Chosen:
C Programming Language

# Why I chose it:

I am learning C from scratch
It helps understand core programming concepts (memory, files, structures)
It is widely used in system-level programming

# End Goal:
To build a working Point of Sale (POS) system that:

Manages inventory and customers
Processes sales transactions
Stores data using files
Generates receipts

2. Quick Summary of the Technology

# What is C?
C is a low-level, procedural programming language used for system programming and embedded systems.

# Where is it used?

Operating systems (e.g., Unix)
Embedded systems
Game engines
Compilers

# Real-world example:
The Linux kernel is written in C.

3. System Requirements
Operating System: Windows / Linux / Mac
Compiler: GCC (MinGW for Windows)
Editor: Visual Studio Code (recommended)
Terminal: Command Prompt / Bash

4. Installation & Setup Instructions
# Step 1: Install GCC
Install MinGW
Add bin folder to PATH
# Step 2: Create Project Files
main.c
inventory.c
customer.c
sales.c
inventory.h
customer.h
sales.h
# Step 3: Compile the Project
gcc main.c inventory.c customer.c sales.c -o pos
# Step 4: Run the Program
pos

5. Minimal Working Example
# Description:
A simple program that writes and reads product data from a file.

# Code:
#include <stdio.h>

struct Product {
    int id;
    char name[50];
    float price;
};

int main() {
    struct Product p = {1, "Sugar", 120.5};

    FILE *file = fopen("product.dat", "wb");
    fwrite(&p, sizeof(p), 1, file);
    fclose(file);

    struct Product readP;

    file = fopen("product.dat", "rb");
    fread(&readP, sizeof(readP), 1, file);
    fclose(file);

    printf("ID: %d\nName: %s\nPrice: %.2f\n",
           readP.id, readP.name, readP.price);

    return 0;
}

# Expected Output:
ID: 1
Name: Sugar
Price: 120.50

6. AI Prompt Journal (Updated)
# Prompt 1

Prompt Used:
“I am a beginner in C programming. Suggest a simple but practical project I can build to improve my skills, and break it into features. Include the extensions to download in VS Code for the project to run successfully.”

AI Response Summary:
Suggested building a POS system and broke it down into modules such as inventory, customers, and sales. Also recommended VS Code extensions like C/C++ support and Code Runner.

Evaluation:
Very helpful in selecting a practical project and understanding the tools required to get started.

# Prompt 2

Prompt Used:
“Help me design a simple POS system in C. What files should I create and what should each file do?”

AI Response Summary:
Provided a modular file structure including main.c, inventory.c, customer.c, and sales.c, along with header files.

Evaluation:
Helped me organize my project professionally and understand modular programming.

# Prompt 3

Prompt Used:
“Show me how to define structures in C for products, customers, and sales records for a POS system.”

AI Response Summary:
Explained how to use struct to define data models for products, customers, and transactions.

Evaluation:
Essential for designing how data is stored and manipulated in the system.

# Prompt 4

Prompt Used:
“Teach me how to store and retrieve data from a binary file in C for my POS system.”

AI Response Summary:
Introduced file handling functions like fopen, fwrite, and fread.

Evaluation:
Critical for implementing persistent storage in the system.

# Prompt 5

Prompt Used:
“Help me write functions in C to add, view, edit, and delete products and store data in a file.”

AI Response Summary:
Provided CRUD (Create, Read, Update, Delete) operations for inventory management.

Evaluation:
Helped build the core functionality of the POS system.

# Prompt 6

Prompt Used:
“How do I ensure that product ID and product name are unique when adding products in C?”

AI Response Summary:
Suggested checking existing records in the file before inserting new data.

Evaluation:
Improved data integrity and made the system more reliable.

# Prompt 7

Prompt Used:
“Help me create a customer management system in C with add, view, edit, and delete functions using file storage.”

AI Response Summary:
Guided implementation of customer CRUD operations similar to inventory.

Evaluation:
Ensured consistency and reusability of logic across modules.

# Prompt 8

Prompt Used:
“Help me implement a sales transaction system in C where I select a customer, select products, check stock, and update inventory.”

AI Response Summary:
Outlined how to process transactions, validate stock, and update quantities after a sale.

Evaluation:
This was the most important feature and significantly improved the system’s functionality.

# Prompt 9

Prompt Used:
“Show me how to generate and save a receipt as a text file in C with date and time.”

AI Response Summary:
Explained how to use fprintf and time functions to create receipt files.

Evaluation:
Added a real-world feature to the system and improved usability.

# Prompt 10

Prompt Used:
“How can I create a simple login system in C that asks for username and password before accessing the program?”

AI Response Summary:
Provided a basic authentication mechanism using hardcoded credentials.

Evaluation:
Improved security and user control in the application.

# Prompt 11

Prompt Used:
“Help me create a menu-driven program in C using loops and switch statements for my POS system.”

AI Response Summary:
Showed how to build an interactive CLI menu using loops and switch-case.

Evaluation:
Made the system user-friendly and easy to navigate.

# Prompt 12

Prompt Used:
“Help me connect all my modules (inventory, customer, sales, login) into one main.c file.”

AI Response Summary:
Explained how to integrate all modules into a single program flow.

Evaluation:
Helped complete the system and ensure all components work together.

# Prompt 13

Prompt Used:
“My C program is not saving data correctly to a file. Help me debug file handling issues.”

AI Response Summary:
Identified possible issues such as incorrect file modes and missing file closures.

Evaluation:
Very useful for debugging and improving reliability.

# Prompt 14

Prompt Used:
“How do I compile and run a multi-file C project using gcc?”

AI Response Summary:
Provided the correct compilation command and explained how linking works.

Evaluation:
Essential for running the complete project successfully.

# Prompt 15

Prompt Used:
“How can I improve my C POS system to make it look more professional for a job application?”

AI Response Summary:
Suggested improvements like better UI, error handling, and code structure.

Evaluation:
Helped refine the project into a portfolio-ready application.

7. Common Issues & Fixes
Error: gcc not recognized

# Fix:

Install MinGW
Add to PATH

Error: File not opening

# Fix:

if (file == NULL) {
    printf("Error opening file\n");
}

Error: Data not saving

# Fix:

Ensure file opened in correct mode (wb, rb)
Always close files

8. References
Official GCC Documentation
C Programming Tutorials (GeeksforGeeks)
Stack Overflow (debugging help)
YouTube tutorials on file handling in C








# PROJECT DOCUENTATION
# POS System in C (Console-based)

This is a simple Point of Sale (POS) system developed in **C language** as part of a software engineering job task.

It uses file storage and a command-line interface (CLI) to manage **inventory**, **customers**, and **sales**, and includes features like login, unique record validation, and receipt generation.

---

## 🚀 Features

### 📦 Inventory Management
- Add new products (must have unique ID & name)
- Edit and delete products
- Minimum stock level warning
- View list of products

### 🧍 Customer Management
- Add new customers (must have unique ID & phone)
- Edit and delete customers
- View list of customers

### 💰 Sales Transactions
- Select only existing customers
- Select multiple products by ID and quantity
- Auto-check for stock availability
- Automatically reduce stock after sale
- Generates and saves a **receipt** to a text file (e.g., `receipt_202506281130.txt`)
- Displays total amount and number of items sold

### 🔐 Login System
- Basic login using username and password before accessing the POS
- Default credentials:
  - Username: `admin`
  - Password: `1234`

---

## 💾 Data Storage
- `inventory.dat` – Binary file to store product records
- `customers.dat` – Binary file to store customer records
- `receipt_*.txt` – Text files containing receipt details for each sale

---

## 🛠️ How to Compile & Run

### 💻 Prerequisites
- GCC compiler (MinGW for Windows)
- Visual Studio Code or any text editor

### 🔧 Compilation Command

```bash
gcc main.c inventory.c customer.c sales.c -o pos
