#include <stdio.h>
#include <stdlib.h> // Required for malloc/free
#include "../include/card_utils.h" // Include our custom header

int main() {
    // --- 1. SETUP STORE INVENTORY (ARRAY) ---
    // Minimal array usage as required
    Item store[3] = {
        {"Gaming Laptop", 80000},
        {"Mechanical Keyboard", 5000},
        {"Wireless Mouse", 2000}
    };

    int totalBill = 0;
    int choice;
    long cardNumber;

    // --- 2. DYNAMIC MEMORY ALLOCATION (DMA) ---
    // Allocating memory for customer name on the heap [cite: 8]
    char *customerName = (char*)malloc(50 * sizeof(char));
    
    // Safety check for memory allocation
    if (customerName == NULL) {
        printf("Memory Error\n");
        return 1;
    }

    // Get Customer Name
    printf("Enter Customer Name: ");
    // scanf reads string, %49s limits input to prevent overflow
    scanf("%49s", customerName);

    // --- 3. STORE MENU ---
    printf("\n--- WELCOME TO THE TECH STORE ---\n");
    printf("1. %s (Rs. %d)\n", store[0].itemName, store[0].price);
    printf("2. %s (Rs. %d)\n", store[1].itemName, store[1].price);
    printf("3. %s (Rs. %d)\n", store[2].itemName, store[2].price);
    printf("Select an item to buy (1-3): ");
    
    // Check if input is a valid integer
    if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
        // Arrays are 0-indexed, so we subtract 1 from choice
        totalBill = store[choice - 1].price;
    } else {
        printf("Invalid selection. Exiting.\n");
        free(customerName); // Free memory before exiting
        return 1;
    }

    printf("\nTotal Bill: Rs. %d\n", totalBill);
    
    // --- 4. CARD PROCESSING ---
    // We use a do-while loop to ensure we get a number, 
    // mimicking the safety of get_long
    int items_read;
    do {
        printf("Enter Card Number to Pay: ");
        items_read = scanf("%li", &cardNumber);
        // Clear keyboard buffer
        while (getchar() != '\n'); 
    } while (items_read != 1);

    // Call our function to identify the card
    int cardType = identify_card_type(cardNumber);
    char *cardName;

    // Assign a string name based on the returned code
    switch(cardType) {
        case 1: cardName = "AMEX"; break;
        case 2: cardName = "MASTERCARD"; break;
        case 3: cardName = "VISA"; break;
        case 4: cardName = "RUPAY"; break;
        default: cardName = "INVALID"; break;
    }

    if (cardType != 0) {
        // --- 5. APPLY DISCOUNT (POINTERS) ---
        // Pass the ADDRESS (&) of totalBill so the function can change it
        apply_discount(&totalBill, cardType);
        
        printf("Final Amount to Pay: Rs. %d\n", totalBill);
        
        // --- 6. SAVE RECEIPT (FILE HANDLING) ---
        save_receipt(customerName, totalBill, cardName);
    } else {
        printf("Card Declined: Invalid Number or Unknown Type.\n");
    }

    // Free the dynamically allocated memory
    free(customerName);
    
    return 0;
}
