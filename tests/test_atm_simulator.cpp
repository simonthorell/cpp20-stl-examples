#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "atm_simulator/atm_simulator.h"
#include "atm_simulator/account_manager.h"

class MockAccountManager : public AccountManager {
public:
    MOCK_METHOD(void, createAccount, (int, double), (override));
    MOCK_METHOD(bool, deleteAccount, (int), (override));
    MOCK_METHOD(void, deposit, (int, double), (override));
    MOCK_METHOD(bool, withdraw, (int, double), (override));
    MOCK_METHOD(std::shared_ptr<Account>, getAccount, (int), (override));
};

// Test for deposit functionality
TEST(ATMTest, DepositMoney) {
    auto mockManager = std::make_shared<MockAccountManager>();
    ATMSimulator atm(mockManager);

    int testAccountNumber = 123456;
    double depositAmount = 500.0;
    double initialBalance = 1000.0; // Initial balance for the account

    // Create a mock account to be returned by getAccount
    auto mockAccount = std::make_shared<Account>(testAccountNumber, initialBalance);

    // Set expectations for the mockManager
    EXPECT_CALL(*mockManager, getAccount(testAccountNumber))
        .WillOnce(testing::Return(mockAccount)); // Return the mock account when getAccount is called
    EXPECT_CALL(*mockManager, deposit(testAccountNumber, depositAmount))
        .Times(1); // Expect deposit to be called once

    // Simulate user input for depositing money
    std::stringstream input;
    input << testAccountNumber << "\n1\n" << depositAmount << "\n0"; // Corrected line breaks

    // Save the original state of cin
    auto originalBuffer = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to use input

    atm.run(); // Run the ATM simulator

    // Further assertions can be added here if needed

    // Reset std::cin to its original state
    std::cin.rdbuf(originalBuffer);
}

// // Test for withdraw functionality
// TEST(ATMTest, WithdrawMoney) {
//     auto mockManager = std::make_shared<MockAccountManager>();
//     ATMSimulator atm(mockManager);

//     int testAccountNumber = 123456;
//     double withdrawalAmount = 200.0;

//     EXPECT_CALL(*mockManager, withdraw(testAccountNumber, withdrawalAmount)).WillOnce(testing::Return(true));

//     // Simulate user input for withdrawing money
//     std::stringstream input;
//     input << testAccountNumber << "\\n2\\n" << withdrawalAmount << "\\n0";
//     std::cin.rdbuf(input.rdbuf());

//     atm.run();

//     // Further assertions can be added here if needed
// }

// // Test for checking balance
// TEST(ATMTest, CheckBalance) {
//     auto mockManager = std::make_shared<MockAccountManager>();
//     ATMSimulator atm(mockManager);

//     int testAccountNumber = 12345;
//     double expectedBalance = 1000.0;

//     auto mockAccount = std::make_shared<Account>(testAccountNumber, expectedBalance);
//     EXPECT_CALL(*mockManager, getAccount(testAccountNumber)).WillOnce(testing::Return(mockAccount));

//     // Simulate user input for checking balance
//     std::stringstream input;
//     input << testAccountNumber << "\\n3\\n0";
//     std::cin.rdbuf(input.rdbuf());

//     atm.run();

//     // Further assertions can be added here if needed
// }