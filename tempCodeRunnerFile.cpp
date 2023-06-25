#include <iostream>
#include "Customer.cpp"
#include <cctype> 
#include <algorithm>
#include <vector>
using namespace std;

// std::transform(input.begin(), input.end(), input.begin(),
// [](unsigned char c){ return std::tolower(c); }); .tolower wasn't working so had to find another method of changing to lowercase, found this on stackoverflow
//LOWERCASE FUNCTION

std::vector<Customer> customerArray;  // vector to store customers in order to store their information to be accessed
Customer currCus;

void createAccount() {
    std::string username, password, name;
    std::cout << "Enter your name, first only: ";
    std::cin >> name;
    std::cout << "Enter your username. Make sure to get it right, as when entered it cannot be changed:";
    std::cin >> username;
    std::cout << "Enter your password. Make sure to remember it, as there is no way to access it otherwise: ";
    std::cin >> password;
    Customer newCustomer(name, 0, 0, username, password);
    customerArray.push_back(newCustomer);  // Push the new customer object into the vector
}

bool attemptLogin() {
    std::string username, password, input;
    std::cout << "Login: Enter username\nIf you do not have an account, please enter \"Sign up\"\nEnter \"Q\" to quit: ";
    std::getline(std::cin, input);

    while (input.compare("Q") != 0) {
        if (input == "Sign up") {
            createAccount();
        } else {
            bool foundUsername = false;
            Customer tempCus;
            for (int i = 0; i < customerArray.size(); i++) {
                if (customerArray[i].username == input) {
                    foundUsername = true;
                    tempCus = customerArray[i];
                    break;
                }
            }
            if (foundUsername) {
                std::cout << "Enter password: ";
                std::cin >> password;
                if (password.compare(tempCus.password) == 0) {
                    std::cout << "Login successful!\n";
                    currCus = tempCus;
                    return true;
                } else {
                    std::cout << "Incorrect password. Try again.\n";
                }
            } else {
                std::cout << "Username not found. Try again or sign up.\n";
            }
        }
        std::cout << "Login: Enter username\nIf you do not have an account, please enter \"Sign up\"\nEnter \"Q\" to quit: ";
        std::cin >> input;
    }

    return false;
}

void mainProgram() {
    bool login = attemptLogin();
    if (login) {
        std::cout << "Name: " + currCus.name;
        std::cout << "Balance: " + currCus.balance;
    }
    else {

    }
}




int main() {
    mainProgram();
    
    return 0;
}