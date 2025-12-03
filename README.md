# Tech Store Discount System 🛒💻

## About The Project
Welcome to the Tech Store! This C program simulates a checkout counter where customers can buy gadgets. The core feature is a realistic payment gateway that validates credit cards and applies special discounts based on the card type.

It combines a store interface with a custom-built credit card validator in a single, easy-to-manage file.

## Key Features
* **Real Card Validation:** Implements **Luhn's Algorithm** to mathematically verify if a credit card number is legitimate.
* **Card Detection:** Automatically detects the card issuer based on prefixes:
    * **AMEX:** Starts with 34 or 37.
    * **Mastercard:** Starts with 51-55.
    * **Visa:** Starts with 4.
    * **RuPay:** Starts with 60 or 65 (Indian Card).
* **Smart Discounts:**
    * **AMEX:** 20% Platinum Discount.
    * **RuPay:** 15% Native Card Discount.
    * **Visa/Mastercard:** 5% Standard Discount.
* **Project Structure:** Follows strict modular guidelines with separate `src` and `include` folders.

## Folder Structure
This project is organized to meet strict submission guidelines:
* `src/`: Contains the main source code (`main.c`) with all store and validation logic.
* `include/`: Contains the header file (`card_utils.h`) as per modularity rules.
* `docs/`: Contains project documentation.

## How to Run It
You only need to compile the main file since all logic is self-contained.

1.  **Open your terminal** inside the project folder.
2.  **Compile the code**:
    ```bash
    gcc src/main.c -o store_app
    ```
3.  **Run the store**:
    ```bash
    ./store_app
    ```
4.  Follow the prompts to enter your name, pick an item, and pay with a card number!

---
*Note: This project was created for the C Programming Major Project.*
