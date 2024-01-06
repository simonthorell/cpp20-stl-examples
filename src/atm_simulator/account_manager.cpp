#include "atm_simulator/account_manager.h"
#include <iostream>

//=============================================================================
// Constructor: AccountManager
// Description: Initializes the account manager with some default accounts.
//=============================================================================
AccountManager::AccountManager() {
    // Add default accounts for testing
    accounts[123456] = std::make_shared<Account>(123456, 1000.0);
    accounts[234567] = std::make_shared<Account>(234567, 2000.0);
    accounts[345678] = std::make_shared<Account>(345678, 3000.0);
}
//=============================================================================
// Function: createAccount
// Description: Creates a new account with the specified account number and
//              initial balance.
//=============================================================================
void AccountManager::createAccount(int accountNumber, double initialBalance) {
    accounts[accountNumber] = std::make_shared<Account>(accountNumber, initialBalance);
    std::cout << "Account created successfully with balance: $" << initialBalance << "\n";
}
//=============================================================================
// Function: deleteAccount
// Description: Deletes the account with the specified account number.
//=============================================================================
bool AccountManager::deleteAccount(int accountNumber) {
    if (accounts.erase(accountNumber)) {
        std::cout << "Account deleted successfully.\n";
        return true;
    }
    std::cout << "Account not found.\n";
    return false;
}
//=============================================================================
// Function: deposit
// Description: Deposits the specified amount into the account with the
//              specified account number.
//=============================================================================
void AccountManager::deposit(int accountNumber, double amount) {
    auto account = getAccount(accountNumber);
    if (account) {
        account->deposit(amount);
        std::cout << "Deposit successful. New Balance: $" << account->getBalance() << "\n";
    } else {
        std::cout << "Account not found.\n";
    }
}
//=============================================================================
// Function: withdraw
// Description: Withdraws the specified amount from the account with the
//              specified account number.
//=============================================================================
bool AccountManager::withdraw(int accountNumber, double amount) {
    auto account = getAccount(accountNumber);
    if (account) {
        if (account->withdraw(amount)) {
            std::cout << "Withdrawal successful. New Balance: $" << account->getBalance() << "\n";
            return true;
        } else {
            std::cout << "Insufficient funds.\n";
        }
    } else {
        std::cout << "Account not found.\n";
    }
    return false;
}
//=============================================================================
// Function: getAccount
// Description: Returns a shared pointer to the account with the specified
//              account number.
//=============================================================================
std::shared_ptr<Account> AccountManager::getAccount(int accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}