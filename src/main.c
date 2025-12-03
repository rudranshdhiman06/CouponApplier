#include <stdio.h>
#include <string.h>
#include "../include/card_utils.h"

// STRUCTURES & DATA
typedef struct {
    char itemName[50];
    int price;
} Item;

// LOGIC FUNCTIONS

// Function to identify the card
int get_card_type(long card_number) {

    long temp_card_number = card_number;
    int sum1 = 0, sum2 = 0;
    int digit_count = 0;
    int position = 1;

    // CHECKSUM LOOP
    while (temp_card_number > 0) {
        int digit = temp_card_number % 10;
        
        if (position % 2 == 0) {
            int sectolastnum = digit * 2;
            int product = sectolastnum / 10 + sectolastnum % 10;
            sum1 = sum1 + product;
        } else {
            sum2 = sum2 + digit;
        }
        
        temp_card_number = temp_card_number / 10;
        digit_count++;
        position++;
    }

    if ((sum1 + sum2) % 10 != 0) return 0; // Invalid checksum

    // CHECK PREFIXES
    long temp2 = card_number;
    while (temp2 >= 100) temp2 = temp2 / 10;
    long temp3 = temp2 / 10;

    if ((temp2 == 34 || temp2 == 37) && digit_count == 15) return 1; // AMEX
    if ((temp2 >= 51 && temp2 <= 55) && digit_count == 16) return 2; // MASTERCARD
    if (temp3 == 4 && (digit_count == 13 || digit_count == 16)) return 3; // VISA
    if ((temp2 == 60 || temp2 == 65) && digit_count == 16) return 4; // RUPAY
    
    return 0; // Invalid
}

// Function to calculate discount
int calculate_final_bill(int billAmount, int cardType) {
    if (cardType == 1) { // AMEX
        printf("\n>> AMEX Detected! Applying 20%% Platinum Discount.\n");
        return billAmount * 0.80; 
    } 
    else if (cardType == 4) { // RUPAY
        printf("\n>> RuPay Detected! Applying 15%% Native Discount.\n");
        return billAmount * 0.85; 
    } 
    else if (cardType == 2 || cardType == 3) { // Visa/Master
        printf("\n>> Standard Card Detected. Applying 5%% Discount.\n");
        return billAmount * 0.95;
    } 
    return billAmount;
}

// MAIN FUNCTION 
int main() {
    // Inventory
    Item store[3] = {
        {"Gaming Laptop", 80000},
        {"Mechanical Keyboard", 5000},
        {"Wireless Mouse", 2000}
    };

    int totalBill = 0;
    int choice;
    int quantity = 1;
    char customerName[50];
    long cardNumber;

    // 1. Get Name
    printf("Enter Customer Name: ");
    scanf("%49s", customerName); 

    // 2. Show Menu
    printf("\n--- WELCOME TO THE TECH STORE ---\n");
    printf("1. %s (Rs. %d)\n", store[0].itemName, store[0].price);
    printf("2. %s (Rs. %d)\n", store[1].itemName, store[1].price);
    printf("3. %s (Rs. %d)\n", store[2].itemName, store[2].price);
    
    printf("Select an item (1-3): ");
    if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
        printf("How many do you want?: ");
        if (scanf("%d", &quantity) == 1 && quantity > 0) {
            totalBill = store[choice - 1].price * quantity;
        } else {
            totalBill = store[choice - 1].price;
        }
    } else {
        printf("Invalid selection.\n");
        return 1;
    }

    printf("\nTotal Bill: Rs. %d\n", totalBill);
    
    // 3. Get Card Number
    do {
        printf("Enter Card Number: ");
        if (scanf("%li", &cardNumber) != 1) {
            while (getchar() != '\n'); // Clear bad input
            cardNumber = 0;
        }
    } while (cardNumber <= 0);

    // 4. Run Logic
    int cardType = get_card_type(cardNumber);

    if (cardType != 0) {
        totalBill = calculate_final_bill(totalBill, cardType);
        printf("Final Amount to Pay: Rs. %d\n", totalBill);
        
        // Simple Receipt Save
        FILE *file = fopen("receipts.txt", "a");
        if (file != NULL) {
            fprintf(file, "Customer: %s | Paid: %d\n", customerName, totalBill);
            fclose(file);
            printf(">> Receipt saved.\n");
        }
    } else {
        printf("Card Declined: Invalid Number or Unknown Type.\n");
    }

    return 0;
}

