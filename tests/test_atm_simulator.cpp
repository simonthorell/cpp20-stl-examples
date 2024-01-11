//==============================================================================
// ATM SIMULATOR TEST SUITE
//==============================================================================
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "atm_simulator/atm_simulator.h"
#include "atm_simulator/account_manager.h"
//=============================================================================
// Class: MockAccountManager
// Description: Mock class for AccountManager
//=============================================================================
class MockAccountManager : public AccountManager {
public:
    MOCK_METHOD(void, createAccount, (int, double), (override));
    MOCK_METHOD(bool, deleteAccount, (int), (override));
    MOCK_METHOD(void, deposit, (int, double), (override));
    MOCK_METHOD(bool, withdraw, (int, double), (override));
    MOCK_METHOD(std::shared_ptr<Account>, getAccount, (int), (override));
};
//=============================================================================
// Test Fixture: SuppressOutputTest
// Description: Provides common setup and teardown functionality for tests that
//              need to suppress output - Will not print to console!
//=============================================================================
// Test Fixture for Suppressing Output
class SuppressOutputTest : public ::testing::Test {
protected:
    std::streambuf* originalCoutBuffer;
    std::streambuf* originalCerrBuffer;
    std::ostringstream capturedCout;
    std::ostringstream capturedCerr;

    void SetUp() override {
        originalCoutBuffer = std::cout.rdbuf();
        originalCerrBuffer = std::cerr.rdbuf();
        std::cout.rdbuf(capturedCout.rdbuf());
        std::cerr.rdbuf(capturedCerr.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);
        std::cerr.rdbuf(originalCerrBuffer);
    }
};
//=============================================================================
// Test Fixture: ATMSimulatorTest
// Description: Provides common setup and teardown functionality for ATM tests.
//=============================================================================
// Test for deposit functionality
// Test for deposit functionality using SuppressOutputTest fixture
TEST_F(SuppressOutputTest, DepositMoneyUI) {
    auto mockManager = std::make_shared<MockAccountManager>();
    ATMSimulator atm(mockManager);

    int testAccountNumber = 123456;
    double depositAmount = 500.0;
    double initialBalance = 1000.0; // Initial balance for the account

    // Create a mock account to be returned by getAccount
    auto mockAccount = std::make_shared<Account>(testAccountNumber, initialBalance);

    // Set expectations for the mockManager
    EXPECT_CALL(*mockManager, getAccount(testAccountNumber))
        .WillOnce(testing::Return(mockAccount)); 
    EXPECT_CALL(*mockManager, deposit(testAccountNumber, depositAmount))
        .Times(1); // Expect deposit to be called once

    // Simulate user input for depositing money
    std::stringstream input;
    input << testAccountNumber << "\n1\n" << depositAmount << "\n0";

    // Redirect cin to use input
    std::cin.rdbuf(input.rdbuf()); 

    atm.run(); // Run the ATM simulator
}

// Test for withdraw functionality
TEST_F(SuppressOutputTest, WithdrawMoneyUI) {
    auto mockManager = std::make_shared<MockAccountManager>();
    ATMSimulator atm(mockManager);

    int testAccountNumber = 223456;
    double withdrawalAmount = 200.0;
    double initialBalance = 1000.0;

    auto mockAccount = std::make_shared<Account>(testAccountNumber, initialBalance);
    EXPECT_CALL(*mockManager, getAccount(testAccountNumber))
        .WillOnce(testing::Return(mockAccount));
    EXPECT_CALL(*mockManager, withdraw(testAccountNumber, withdrawalAmount))
        .WillOnce(testing::Return(true));

    std::stringstream input;
    input << testAccountNumber << "\n2\n" << withdrawalAmount << "\n0";
    std::cin.rdbuf(input.rdbuf());

    atm.run();
}

// Test for check balance functionality
TEST_F(SuppressOutputTest, CheckBalanceUI) {
    auto mockManager = std::make_shared<MockAccountManager>();
    ATMSimulator atm(mockManager);

    int testAccountNumber = 323456;
    double expectedBalance = 1038.0;

    auto mockAccount = std::make_shared<Account>(testAccountNumber, expectedBalance);
    EXPECT_CALL(*mockManager, getAccount(testAccountNumber))
        .WillRepeatedly(testing::Return(mockAccount));

    std::stringstream input;
    input << testAccountNumber << "\n3\n0";
    std::cin.rdbuf(input.rdbuf());

    atm.run();
}