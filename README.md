# Tech Store Discount System 🛒💻

## About The Project
Welcome to the Tech Store! This C program simulates a checkout counter where customers can buy gadgets. But the cool part isn't the shopping—it's the payment system.

The program acts as a real-world payment gateway. It takes a credit card number, uses math to check if it's valid (so you can't just make up numbers), and then figures out which bank issued it. Based on the card type—like AMEX or RuPay—it applies special discounts to your bill!

## Key Features
* **Real Card Validation:** I implemented **Luhn's Algorithm** from scratch to mathematically verify if a card number is legitimate.
* **Card Detection:** The system checks prefixes to identify **VISA, Mastercard, AMEX**, and even **Indian RuPay cards**.
* **Smart Discounts:** * *AMEX* users get a massive Platinum discount.
    * *RuPay* users get a special "Native Card" discount.
* **Under the Hood:**
    * **Pointers:** Used to modify the bill amount directly in memory.
    * **File Handling:** Automatically saves every transaction to a `receipts.txt` file so there's a permanent record.

## How to Run It
If you want to try it out, you'll need a C compiler (like GCC).

1.  Open your terminal inside this project folder.
2.  Compile the code by running this command:
    ```bash
    gcc src/main.c src/card_utils.c -o store_app
    ```
3.  Launch the store:
    ```bash
    ./store_app
    ```
4.  Follow the on-screen prompts to buy something and try different card numbers!
