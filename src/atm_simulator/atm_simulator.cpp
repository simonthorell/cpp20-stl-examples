#include "atm_simulator/atm_simulator.h"
#include <iostream>
#include <limits>

//=============================================================================
// Constructor: ATMSimulator
// Description: Initializes the ATM system with the specified AccountManager.
//=============================================================================
ATMSimulator::ATMSimulator(std::shared_ptr<AccountManager> manager) : manager(manager) {}

//=============================================================================
// Function: displayMenu
// Description: Displays the ATM menu.
//=============================================================================

void ATMSimulator::displayMenu() {
    std::cout << "ATM Menu:\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. Check Balance\n";
    std::cout << "4. Delete Account\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}
//=============================================================================
// Function: processUserSelection
// Description: Processes the user's selection from the menu.
//=============================================================================
void ATMSimulator::processUserSelection(int selection, int accountNumber) {
    double amount;
    switch (selection) {
        case 1: // Deposit
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            manager->deposit(accountNumber, amount);
            break;
        case 2: // Withdraw
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            if (!manager->withdraw(accountNumber, amount)) {
                std::cout << "Unable to withdraw the specified amount.\n";
            }
            break;
        case 3: // Check Balance
            {
                auto account = manager->getAccount(accountNumber);
                if (account) {
                    std::cout << "Account Balance: $" << account->getBalance() << "\n";
                } else {
                    std::cout << "Account not found.\n";
                }
                break;
            }
        case 4: // Delete Account
            if (manager->deleteAccount(accountNumber)) {
                std::cout << "Exiting...\\n";
                selection = 0; // To exit after deleting
            }
            break;
        default:
            std::cout << "Invalid selection. Please try again.\n";
    }
}
//=============================================================================
// Function: run
// Description: Starts the ATM system.
//=============================================================================
char ATMSimulator::run() {
    int accountNumber;
    std::cout << "Please enter your account number: ";
    std::cin >> accountNumber;
    auto account = manager->getAccount(accountNumber);

    if (!account) {
        char choice;
        std::cout << "Account not found. Would you like to create a new account? (y/n): ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            double initialBalance;
            std::cout << "Enter initial balance for the new account: ";
            std::cin >> initialBalance;
            manager->createAccount(accountNumber, initialBalance);
        } else {
            return 0; // Exit if the user doesn't want to create a new account
        }
    }

    int selection;
    do {
        displayMenu();
        std::cin >> selection;
        // Clear the input buffer to handle any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        processUserSelection(selection, accountNumber);
    } while (selection != 0); // Assuming 0 is the exit option

    return 0;
}