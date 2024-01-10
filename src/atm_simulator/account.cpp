#include "atm_simulator/account.h"

//=============================================================================
// Constructor: Account
// Description: Initializes the account with the specified account number and
//              initial balance.
//=============================================================================
Account::Account(int accountNumber, double balance)
    : accountNumber(accountNumber), balance(balance) {}
//=============================================================================
// Getters: getAccountNumber & getBalance
// Description: Returns the account number and balance.
//=============================================================================
int Account::getAccountNumber() const {
    return accountNumber;
}

double Account::getBalance() const {
    return balance;
}
//=============================================================================
// Methods: deposit & withdraw
// Description: Deposits or withdraws the specified amount from the account.
//=============================================================================
void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > balance) return false;
    balance -= amount;
    return true;
}