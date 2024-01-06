#include "atm_simulator/account.h"

//=============================================================================
// Constructor: Account
// Description: Initializes the account with the specified account number and
//              initial balance.
//=============================================================================
Account::Account(int accountNumber, double balance)
    : accountNumber(accountNumber), balance(balance) {}
//=============================================================================
// Method: getAccountNumber
// Description: Returns the account number.
//=============================================================================
int Account::getAccountNumber() const {
    return accountNumber;
}
//=============================================================================
// Method: getBalance
// Description: Returns the account balance.
//=============================================================================
double Account::getBalance() const {
    return balance;
}
//=============================================================================
// Method: deposit
// Description: Deposits the specified amount into the account.
//=============================================================================
void Account::deposit(double amount) {
    balance += amount;
}
//=============================================================================
// Method: withdraw
// Description: Withdraws the specified amount from the account.
//=============================================================================
bool Account::withdraw(double amount) {
    if (amount > balance) return false;
    balance -= amount;
    return true;
}