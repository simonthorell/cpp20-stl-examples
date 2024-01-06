#ifndef ATM_SIMULATOR_H
#define ATM_SIMULATOR_H

#include "atm_simulator/account_manager.h"

class ATMSimulator {
public:
    // Constructor to initialize the ATM system with the AccountManager
    ATMSimulator(std::shared_ptr<AccountManager> manager);
    // Method to start the ATM system
    char run(); 

private:
    // Instance of AccountManager
    std::shared_ptr<AccountManager> manager;

    // Class Methods
    void displayMenu();
    void processUserSelection(int selection, int accountNumber);
};

#endif // ATM_SIMULATOR_H