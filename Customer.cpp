#include <string>
class Customer {
    public:
        std::string name, username, password;
        int balance, accNumber;

        Customer() {}

        //Constructor with basic variables expected in bank accounts. Note: balance is in cents to avoid floating point errors, ex. 10000 = $100.00
        Customer(std::string name, int balance, int accNumber, std::string username, std::string password) {
            this->name = name;
            this->balance = balance;
            this->accNumber = accNumber;
            this->username = username;
            this->password = password;
        }
    
};