#ifndef ATM_SIMULATOR_H
#define ATM_SIMULATOR_H

#include <map>

class ATMSimulator {
private:
    int accountNumber;
    double balance;
    char transactionType;
    std::map<int, double> bankAccounts;

public:
    ATMSimulator(); // Constructor
    char Run(); // Main Method

    // Utility Methods
    int GetAccountNumber();
    double GetBalance();
    void SetBalance(double balance);
    void CreateAccount();
    void DeleteAccount();

private:
    // ATM Display Methods (TODO: Move to a separate class?)
    void InputAccountNumber();
    void InputTransactionType();
    void ProcessTransaction();
    void HandleBalanceInquiry();
    void HandleDeposit();
    void HandleWithdrawal();
};

#endif // ATM_SIMULATOR_H