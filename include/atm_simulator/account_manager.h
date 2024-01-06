#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "atm_simulator/account.h"
#include <unordered_map>
#include <memory>

class AccountManager {
public:
    // Constructor to add defualt accounts
    AccountManager();
    // Class Methods
    virtual void createAccount(int accountNumber, double initialBalance);
    virtual bool deleteAccount(int accountNumber);
    virtual void deposit(int accountNumber, double amount);
    virtual bool withdraw(int accountNumber, double amount);
    virtual std::shared_ptr<Account> getAccount(int accountNumber);

private:
    // Map of Bank Accounts 
    std::unordered_map<int, std::shared_ptr<Account>> accounts;
};

#endif // ACCOUNT_MANAGER_H