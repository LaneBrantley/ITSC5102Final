#include <string>
#include <iostream>
#include <iomanip> // Include the <iomanip> header for formatting

class Customer {
    public:
        //All attributes of Customer objects
        std::string name, username, password;
        int balance, accNumber;

        Customer() {} //Default constructor

        //Constructor with basic variables expected in bank accounts. Note: balance is in cents to avoid floating point errors, ex. 10000 = $100.00
        Customer(std::string name, int balance, int accNumber, std::string username, std::string password) {
            this->name = name;
            this->balance = balance;
            this->accNumber = accNumber;
            this->username = username;
            this->password = password;
        }

        //Method for returning a string with the amount in cents to dollar format. ex. if amount = 12345, this returns $123.45
        std::string centsToDollar(int amount) {
            int dollars, cents;
            std::string formattedAmount;
            dollars = amount / 100;
            cents = amount % 100;
            formattedAmount = "$" + std::to_string(dollars) + ".";
            if (cents < 10) {
                formattedAmount += "0";
            }
            formattedAmount += std::to_string(cents);
            return formattedAmount;
        }

        //Method for depositing into bank account. Works in the way of 
        void deposit() {
            int amount;
            std::cout << "How much would you like to deposit? Enter in cents, i.e. 100 = 1.00: ";
            std::cin >> amount;

            if (amount <= 0) {
                std::cout << "Amount entered must be greater than 0. Please try again.";
            }
            else {
                balance += amount;
                std::cout << centsToDollar(amount) << " has been added to your account" << std::endl;
                std::cin.ignore();
            }
        }
        //Method for withdrawing from account. Logic is: if greater than balance, no withdraw. If not positive, no withdraw. Else, withdraws from account. 
        void withdraw() {
            int amount;
            std::cout << "How much would you like to withdraw? Enter in cents, i.e. 100 = 1.00: ";
            std::cin >> amount;

            if (amount > balance) {
                std::cout << "You do not have that much in your account. Your balance is: " << balance;
            }
            else if (amount <= 0) {
                std::cout << "Amount entered must be greater than 0. Please try again. " << std::endl;
            }
            else {
                balance -= amount;
                std::cout << centsToDollar(amount) << " has been withdrawn from your account" << std::endl;
                std::cin.ignore();
            }
        }
        // Method to show balance in dollar format instead of in cents
        void getBalance() {
            std::cout << "Balance: " << centsToDollar(balance) << std::endl;
        }

        //Accessor for account number. Requires password verification to access it for privacy reasons
        void getAccNumber() {
            std::string input;
            int passwordFails = 0; //Variable to see if user fails password too many times. If failed 3 times, function will not return account number
            std::cout << "Enter your password: ";
            std::cin >> input;
            while (input != password) {
                std::cin.ignore();
                passwordFails++;
                if (passwordFails >= 3) {
                    break;
                }
                std::cout << "Incorrect. Try again" << std::endl;
                std::cout << "Enter your password: ";
                std::cin >> input;
            }

            if (passwordFails < 3) {
                std::cout << "Your account number is: " << accNumber << std::endl;
                std::cin.ignore();
            }
            else {
                std::cout << "Failed password too many times. Try again later." << std::endl;
            }
        }
};