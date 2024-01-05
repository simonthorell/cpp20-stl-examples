#include <gtest/gtest.h>
#include "atm_simulator/atm_simulator.h"

class ATMSimulatorTest : public ::testing::Test {
protected:
    ATMSimulator atm;
};

// Test the constructor ensures the initial balance is correct.
TEST_F(ATMSimulatorTest, ConstructorInitialBalanceTest) {
    EXPECT_EQ(atm.GetBalance(), 0.0);
}

// Test the SetBalance and GetBalance methods.
TEST_F(ATMSimulatorTest, SetGetBalanceTest) {
    atm.SetBalance(1000.0);
    EXPECT_EQ(atm.GetBalance(), 1000.0);
}