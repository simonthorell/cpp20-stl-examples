#include "atm_simulator/atm_simulator.h"
#include <iostream>

//=============================================================================
//                      Constructor for ATM Simulator Class
//=============================================================================

ATMSimulator::ATMSimulator () {
    // Initialize some random bank accounts in the map
    bankAccounts[123456] = 1000.0;
    bankAccounts[234567] = 2000.0;
    bankAccounts[345678] = 3000.0;

    // Initialize balance to 0.0
    balance = 0.0;
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

void ATMSimulator::CreateAccount () {
    // TODO: Implement
    /* Using map accounts are always sorted based on their keys in ascending order. 
     * So, if we want to create a new account, we can simply use the last key in
    * the map and increment it by 1. */
}

void ATMSimulator::DeleteAccount () {
    // TODO: Implement
}

//=============================================================================
//                            ATM Display Methods
//=============================================================================

void ATMSimulator::InputAccountNumber() {
    while (true) {
        std::cout << "Please enter your account number: ";
        std::cin >> accountNumber;
        if (bankAccounts.find(accountNumber) == bankAccounts.end()) {
            std::cout << "Invalid account number. Please try again.\n";
        } else {
            break;
        }
    }
}

void ATMSimulator::InputTransactionType() {
    std::string types = "(B = Balance, D = Deposit, W = Withdrawal, Q = Quit): ";

    while (true) {
        std::cout << "Please enter your transaction type " << types;

        std::cin >> transactionType;
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