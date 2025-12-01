#include <stdio.h>
#include <string.h>
#include "../include/card_utils.h"

// Function to identify card type
// Returns: 1 for AMEX, 2 for MASTERCARD, 3 for VISA, 4 for RUPAY, 0 for INVALID
int identify_card_type(long card_number) {
    
    // STEP 1: LUHN'S ALGORITHM (YOUR ORIGINAL CODE)
    
    // Variables for checksum calculation
    long temp_card_number = card_number;
    int sum1 = 0;
    int sum2 = 0;
    int digit_count = 0;
    int position = 1; // Tracks if we are at an odd or even position

    while (temp_card_number > 0)
    {
        // Get the last digit
        int digit = temp_card_number % 10;

        // If position is even, multiply by 2 and add digits of product
        if (position % 2 == 0)
        {
            int sectolastnum = digit * 2;
            // The trick to add digits of a number (e.g., 14 -> 1+4=5)
            int product = sectolastnum / 10 + sectolastnum % 10;
            sum1 = sum1 + product;
        }
        else
        {
            // If position is odd, just add the digit
            sum2 = sum2 + digit;
        }

        // Remove the last digit to move to the next one
        temp_card_number = temp_card_number / 10;

        digit_count++;
        position++;
    }

    int finalsum = sum1 + sum2;

    // Check if the checksum is valid (must end in 0)
    if (finalsum % 10 != 0) {
        return 0; // Invalid checksum
    }

    // STEP 2: CHECK PREFIXES (YOUR ORIGINAL LOGIC)
    
    // Get the first two digits (stored in temp2)
    long temp2 = card_number;
    while (temp2 >= 100)
    {
        temp2 = temp2 / 10;
    }

    // Get the first single digit (stored in temp3)
    long temp3 = temp2 / 10;

    // STEP 3: FINAL DECISION CHAIN
    
    // AMEX: Starts with 34 or 37, length 15
    if ((temp2 == 34 || temp2 == 37) && digit_count == 15)
    {
        return 1; // Code 1 for AMEX
    }
    // MASTERCARD: Starts with 51-55, length 16
    else if ((temp2 >= 51 && temp2 <= 55) && digit_count == 16)
    {
        return 2; // Code 2 for MASTERCARD
    }
    // VISA: Starts with 4, length 13 or 16
    else if ((temp3 == 4) && (digit_count == 13 || digit_count == 16))
    {
        return 3; // Code 3 for VISA
    }
    // RUPAY (Indian Card): Starts with 60 or 65, length 16 (Added feature)
    else if ((temp2 == 60 || temp2 == 65) && digit_count == 16)
    {
        return 4; // Code 4 for RUPAY
    }
    else
    {
        return 0; // Valid checksum, but unknown company
    }
}

// Function to modify the bill using a POINTER [cite: 8]
void apply_discount(int *billAmount, int cardType) {
    // We use the pointer *billAmount to directly change the value in main memory
    
    if (cardType == 1) { 
        // AMEX gets a Platinum discount (20%)
        printf("\n>> AMEX Detected! Applying 20%% Platinum Discount.\n");
        *billAmount = *billAmount * 0.80; 
    } 
    else if (cardType == 4) { 
        // RuPay gets a Native card discount (15%)
        printf("\n>> RuPay Detected! Applying 15%% Native Discount.\n");
        *billAmount = *billAmount * 0.85; 
    } 
    else if (cardType == 2 || cardType == 3) { 
        // Standard Visa/MasterCard discount (5%)
        printf("\n>> Standard Card Detected. Applying 5%% Discount.\n");
        *billAmount = *billAmount * 0.95;
    } 
    else {
        printf("\n>> Unknown Card Type. No Discount Applied.\n");
    }
}

// Function to demonstrate FILE HANDLING [cite: 8]
void save_receipt(char *name, int finalAmount, char *cardName) {
    // 'a' mode appends to the file instead of overwriting it
    FILE *file = fopen("receipts.txt", "a");
    
    // Always check if file opened successfully
    if (file == NULL) {
        printf("Error: Could not save receipt.\n");
        return;
    }
    
    // Write the transaction details to the file
    fprintf(file, "Customer: %s | Paid: Rs. %d | Via: %s\n", name, finalAmount, cardName);
    
    fclose(file); // Always close the file to save data
    printf(">> Receipt saved successfully to receipts.txt\n");
}

