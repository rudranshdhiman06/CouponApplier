#include <stdio.h>
#include <stdlib.h> 
#include "../include/card_utils.h"

int main() {
    // SETUP STORE INVENTORY
    // Simple array of items
    Item store[3] = {
        {"Gaming Laptop", 80000},
        {"Mechanical Keyboard", 5000},
        {"Wireless Mouse", 2000}
    };

    int totalBill = 0;
    int choice;
    int quantity = 1;
    long cardNumber;

    //CUSTOMER NAME
    char customerName[50];

    printf("Enter Customer Name: ");
    scanf("%49s", customerName); 

    // STORE MENU
    printf("\n--- WELCOME TO THE TECH STORE ---\n");
    printf("1. %s (Rs. %d)\n", store[0].itemName, store[0].price);
    printf("2. %s (Rs. %d)\n", store[1].itemName, store[1].price);
    printf("3. %s (Rs. %d)\n", store[2].itemName, store[2].price);
    
    printf("Select an item to buy (1-3): ");
    
    if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
        
        printf("How many do you want?: ");
        if (scanf("%d", &quantity) == 1 && quantity > 0) {
            totalBill = store[choice - 1].price * quantity;
        } else {
            printf("Invalid quantity. Defaulting to 1.\n");
            totalBill = store[choice - 1].price;
        }

    } else {
        printf("Invalid selection. Exiting.\n");
        return 1;
    }

    printf("\nTotal Bill for %d item(s): Rs. %d\n", quantity, totalBill);
    
    // CARD PROCESSING
    int items_read;
    do {
        printf("Enter Card Number to Pay: ");
        items_read = scanf("%li", &cardNumber);
        while (getchar() != '\n'); 
    } while (items_read != 1);

    int cardType = identify_card_type(cardNumber);
    char *cardName;

    switch(cardType) {
        case 1: cardName = "AMEX"; break;
        case 2: cardName = "MASTERCARD"; break;
        case 3: cardName = "VISA"; break;
        case 4: cardName = "RUPAY"; break;
        default: cardName = "INVALID"; break;
    }

    if (cardType != 0) {
        // APPLY DISCOUNT
        // The function calculates the new price and sends it back (returns it).
        totalBill = calculate_discount(totalBill, cardType);
        
        printf("Final Amount to Pay: Rs. %d\n", totalBill);
        
        save_receipt(customerName, totalBill, cardName);
    } else {
        printf("Card Declined: Invalid Number or Unknown Type.\n");
    }

    // No need to free(customerName) anymore!
    
    return 0;
}
