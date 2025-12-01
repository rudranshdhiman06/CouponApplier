#ifndef CARD_UTILS_H
#define CARD_UTILS_H

#include <stdio.h>

// STRUCTURE DEFINITION
// We use this to satisfy the "Structure" requirement of the project. [cite: 8]
typedef struct {
    char itemName[50];
    int price;
} Item;

// FUNCTION PROTOTYPES
// These tell the compiler that these functions exist in another file.
// 1. Function to check card validity using Luhn's algorithm and prefixes
int identify_card_type(long card_number);

// 2. Function to apply discount based on card type (Demonstrates Pointers)
void apply_discount(int *billAmount, int cardType);

// 3. Function to save the transaction to a file (Demonstrates File Handling)
void save_receipt(char *name, int finalAmount, char *cardName);

#endif
