#include "atm_simulator/atm_simulator.h"
#include <iostream>
#include <cctype>   // For toupper()

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

    // Prompt user for account number
    InputAccountNumber();
    balance = bankAccounts[accountNumber];
    
    // Prompt user for transaction type until requested to quit
    while (transactionType != 'Q') {
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
    // Generate a new account number by finding the highest existing 
    // account number and adding 1.
    int newAccountNumber = bankAccounts.rbegin()->first + 1;

    // Set the initial balance of the new account.
    double initialBalance = 0.0;
    
    // Insert the new account into the bankAccounts map.
    bankAccounts[newAccountNumber] = initialBalance;

    std::cout << "New account created successfully. Account Number: " 
              << newAccountNumber << " with balance $" << initialBalance 
              << "\n";
}

void ATMSimulator::DeleteAccount() {
    // Prompt the user for the account number to delete.
    std::cout << "Enter the account number you wish to delete: ";
    int accountToDelete;
    std::cin >> accountToDelete;

    // Check if the account exists.
    if (bankAccounts.find(accountToDelete) != bankAccounts.end()) {
        // Delete the account.
        bankAccounts.erase(accountToDelete);
        std::cout << "Account " << accountToDelete 
                  << " has been successfully deleted.\n";
    } else {
        // Account number not found.
        std::cout << "Account number " << accountToDelete << " does not exist.\n";
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
            std::cout << "Account number not found. Create new account? (Y/N)\n";
            char createNewAccount;
            std::cin >> createNewAccount;
            if (createNewAccount == 'Y') {
                CreateAccount();
            } else {
                std::cout << "Please enter account number again.\n";
            }
        } else {
            break;
        }
    }
}

void ATMSimulator::InputTransactionType() {
    std::string types = "(B = Balance, D = Deposit, W = Withdrawal, Q = Quit): ";

    while (true) {
        std::cout << "Please enter your transaction type " << types;
        char input;
        std::cin >> input;
        transactionType = toupper(input);

        if (transactionType == 'B' || transactionType == 'D' || 
            transactionType == 'W' || transactionType == 'Q') {
                ProcessTransaction();
        } else {
            std::cout << "Invalid transaction type. Please try again.\n";
        }

        if (transactionType == 'Q') {
            break;  // Exit the loop if 'Q' is entered
        }
    }
}

void ATMSimulator::ProcessTransaction() {
    switch (transactionType) {
        case 'B':
            HandleBalanceInquiry();
            break;
        case 'D':
            HandleDeposit();
            break;
        case 'W':
            HandleWithdrawal();
            break;
        case 'Q':
            std::cout << "Thank you for using the ATM Simulator!\n";
            break;
        default:
            std::cout << "Invalid transaction type. Please try again.\n";
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