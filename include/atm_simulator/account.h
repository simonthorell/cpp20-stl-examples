#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
    // Constructor
    Account(int accountNumber, double balance);

    // Class Methods
    int getAccountNumber() const;
    double getBalance() const;
    void deposit(double amount);
    bool withdraw(double amount);

private:
    int accountNumber;
    double balance;
};

#endif // ACCOUNT_H