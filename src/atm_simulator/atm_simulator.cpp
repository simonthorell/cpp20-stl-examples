#include "atm_simulator/atm_simulator.h"
#include <iostream>

//=============================================================================
//                      Constructor for ATM Simulator Class
//=============================================================================

ATMSimulator::ATMSimulator () {
    // Initialize some random bank accounts in the map
    bankAccounts[1] = 1000.0; // Account number 1 with balance $1000.0
    bankAccounts[2] = 2000.0; // Account number 2 with balance $2000.0
    bankAccounts[3] = 3000.0; // Account number 3 with balance $3000.0
}

//=============================================================================
//                               Class Main Method
//=============================================================================

char ATMSimulator::Run () {
    std::cout << "Welcome to the ATM Simulator!\n";

    while (transactionType != '5') {
        if (accountNumber == 0) {
            // Prompt user for account number
            InputAccountNumber();
            balance = bankAccounts[accountNumber];
        }
        // Prompt user for transaction type until requested to quit
        InputTransactionType();
    }

    // Reset variables for next ATM user
    accountNumber = 0;
    balance = 0.0;
    transactionType = '0';

    return 0;
}

//=============================================================================
//                              Utility Methods
//=============================================================================

int ATMSimulator::GetAccountNumber () {
    return accountNumber;
}

double ATMSimulator::GetBalance () {
    return balance;
}

void ATMSimulator::SetBalance (double balance) {
    this->balance = balance;
}

void ATMSimulator::CreateAccount() {
    /* Generate a new account number by finding the highest existing 
     * account number and adding 1. This will be faster than iterating
     * from the beginning to find an empty slot */
    int newAccountNumber = bankAccounts.rbegin()->first + 1;
    // Set the initial balance of the new account.
    double initialBalance = 0.0;
    // Insert the new account into the bankAccounts map.
    bankAccounts[newAccountNumber] = initialBalance;

    std::cout << "New account created successfully. Account Number: " 
              << newAccountNumber << " with balance $" << initialBalance 
              << "\n";

    // Set the account number to the new account.
    accountNumber = newAccountNumber;
}

void ATMSimulator::DeleteAccount() {
    // Check if the account exists.
    if (bankAccounts.find(accountNumber) != bankAccounts.end()) {
        // Delete the account.
        bankAccounts.erase(accountNumber);
        std::cout << "Account " << accountNumber 
                  << " has been successfully deleted.\n";
        accountNumber = 0; // Reset account number to 0.
    } else {
        // Account number not found.
        std::cout << "Account number " << accountNumber << " does not exist.\n";
    }
}

//=============================================================================
//                            ATM Display Methods
//=============================================================================

void ATMSimulator::InputAccountNumber() {
    while (true) {
        std::cout << "Please enter your account number: ";
        std::cin >> accountNumber;
        if (bankAccounts.find(accountNumber) == bankAccounts.end()) {
            std::cout << "Account number not found. Create new account? (Y/N): ";
            char createNewAccount;
            std::cin >> createNewAccount;
            if (createNewAccount == 'Y') {
                CreateAccount();
                return;
            } else {
                std::cout << "Please enter account number again.\n";
            }
        } else {
            break;
        }
    }
}

void ATMSimulator::AccountMenu() {
    std::cout << "Account Menu\n";
    std::cout << "1. Balance Inquiry\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Withdrawal\n";
    std::cout << "4. Delete Account\n";
    std::cout << "5. Quit\n";
}

void ATMSimulator::InputTransactionType() {
    AccountMenu();
    while (accountNumber != 0) {
        std::cout << "Please enter your transaction type (1-5): ";
        std::cin >> transactionType;

        if (transactionType >= '1' && transactionType <= '5') {
                ProcessTransaction();
        } else {
            std::cout << "Invalid transaction type. Please try again.\n";
        }

        if (transactionType == '5') {
            break;  // Exit the loop if 'Q' is entered
        }
    }
}

void ATMSimulator::ProcessTransaction() {
    switch (transactionType) {
        case '1':
            HandleBalanceInquiry();
            break;
        case '2':
            HandleDeposit();
            break;
        case '3':
            HandleWithdrawal();
            break;
        case '4':
            DeleteAccount();
            break;
        case '5': // Exit
            std::cout << "Thank you for using the ATM Simulator!\n";
            break;
    }
}

void ATMSimulator::HandleBalanceInquiry() {
    std::cout << "Your balance is $" << GetBalance() << "\n";
}

void ATMSimulator::HandleDeposit() {
    std::cout << "Please enter the amount you would like to deposit: ";
    double depositAmount;
    std::cin >> depositAmount;
    SetBalance(GetBalance() + depositAmount);
    std::cout << "Your new balance is $" << GetBalance() << "\n";
}

void ATMSimulator::HandleWithdrawal() {
    std::cout << "Please enter the amount you would like to withdraw: ";
    double withdrawalAmount;
    std::cin >> withdrawalAmount;
    if (withdrawalAmount > GetBalance()) {
        std::cout << "Insufficient funds. Please try again.\n";
    } else {
        SetBalance(GetBalance() - withdrawalAmount);
        std::cout << "Your new balance is $" << GetBalance() << "\n";
    }
}