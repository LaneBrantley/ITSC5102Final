#include <iostream>
#include "Customer.cpp"
#include <cctype> 
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#include <random>
#include <cstring>


std::vector<Customer> customerArray;  // vector to store customers in order to store their information to be accessed
Customer *currCus; // Pointer variable of a customer object. Used to allow login and manipulation to reflect on the actual object

//Method to transform strings to lowercase, used with input so if user inputs "Q" or "q", it will still work. 
std::string lowercase(std::string& phrase) {
    std::string result = phrase;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

//Method for looping through array to find username of user. Used in createAccount() and attemptLogin()
bool foundUsername(std::string username) {
    bool foundUsername = false;
    for (int i = 0; i < customerArray.size(); i++) { //Loops through customer vector
        if (customerArray[i].username == username) {
            foundUsername = true;
        }
    }
    return foundUsername;
}

void createAccount() {
    std::string username, password, name;
    std::cout << "Enter your name, first only: ";
    std::cin >> name;
    std::cout << "Enter your username. Make sure to get it right, as when entered it cannot be changed: ";
    std::cin >> username;
    while (foundUsername(username)) { //Checks to see if username already exists
        std::cout << "Username already in use. Please try again: ";
        std::cin >> username;
    }
    std::cout << "Enter your password. Make sure to remember it, as there is no way to access it otherwise: ";
    std::cin >> password;

    //This block is a random number generator to make account number random for new customer
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 10000000);
    int randomNum = distribution(generator);

    Customer newCustomer(name, 0, randomNum, username, password);
    customerArray.push_back(newCustomer);  // Push the new customer object into the vector
    std::cin.ignore(); //Clear the std::cin for the next call, otherwise attempLogin will print the prompt twice
}

//Function that handles logging into account
bool attemptLogin() {
    std::string input, username, password; // Variables necessary for login
    while (lowercase(input) != "q") { //Q is the quit button, so when input is "Q", the loop breaks and ends
        std::cout << "Login: Enter username\nIf you do not have an account, please enter \"Sign up\"\nEnter \"q\" to quit: " << std::endl;
        std::getline(std::cin, input);
        if (lowercase(input) == "sign up") { // Calls the createAccount method to create a new customer object 
            createAccount();
        } 
        else { // If it is a username, goes through algorithm to find customer
            int index;
            bool foundUsername = false;
            std::string tempPassword;
            for (int i = 0; i < customerArray.size(); i++) { //Loops through customer vector. Using same loop as foundUsername() but also needs the customer object so needs to be here as well
                if (customerArray[i].username == input) {
                    foundUsername = true;
                    tempPassword = customerArray[i].password; // Copies object's password to tempPassword to allow for password checking
                    index = i;
                }
            }
            if (foundUsername) { //If one of the customers in the vector matches the username entered, password is verified
                std::cout << "Enter password: ";
                std::cin >> password;
                if (password == tempPassword) {
                    std::cout << "Login successful!\n";
                    currCus = &customerArray[index]; // If password is correct, currCus becomes a pointer variable to the actual Customer object
                    return true; // Returns true to allow mainProgram() to go into the if block 
                } 
                else {
                    std::cout << "Incorrect password. Try again.\n";
                    std::cin.ignore();
                }
            } 
            else if (lowercase(input) == "q") {
                return false; //Returns false if q is entered, causing the program to end. 
            }
            else {
                std::cout << "Username not found. Try again or sign up.\n";
            }
        }
    }
}

//Control of the program. If the user logs in, it goes into the if block to allow the user to use the bank account. 
void mainProgram() {
    std::string input;
    if (attemptLogin()) { //If attemptLogin() returns true: 

        while (lowercase(input) != "q") { //If q is entered, the app shuts down

            //Input to determine what the user wants to do
            std::cout << "Name: " << currCus->name << std::endl;
            currCus->getBalance();
            std::cout << "What would you like to do? Enter \"d\" for deposit, \"w\" for withdraw, \"n\" for account number, \"q\" to quit: ";
            std::getline(std::cin, input);

            //Calls withdraw method on the customer object
            if (lowercase(input) == "w") {
                currCus->withdraw();
            }

            //Calls deposit on the customer object
            else if (lowercase(input) == "d") {
                currCus->deposit();
            }

            //Calls getAccountNumber on customer object
            else if (lowercase(input) == "n") {
                currCus->getAccNumber();
            }
        }
        std::cout << "Thank you for using our bank! Goodbye. ";
    }
}

//Function that is compiled, which calls mainProgram()
int main() {
    mainProgram();
    
    return 0;
}