#ifndef ATM_SIMULATOR_H
#define ATM_SIMULATOR_H

#include <map>

class ATMSimulator {
public:
    // Constructor
    ATMSimulator();
    // Main Function
    char Run();
private:
    // ATM Variables
    int accountNumber;
    double balance;
    char transactionType;

    // Initialize some random bank accounts in the map
    std::map<int, double> bankAccounts;

    // Utility Functions
    int GetAccountNumber();
    double GetBalance();
    void SetBalance(double balance);
    void CreateAccount();
    void DeleteAccount();

    // ATM Display Functions (TODO: Move to a separate class?)
    void InputAccountNumber();
    void InputTransactionType();
    void ProcessTransaction();
    void HandleBalanceInquiry();
    void HandleDeposit();
    void HandleWithdrawal();
};

#endif // ATM_SIMULATOR_H