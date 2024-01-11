//==============================================================================
// QUEUE SIMULATOR TEST SUITE
//==============================================================================
#include <gtest/gtest.h>
#include <sstream>
#include "queue_simulator/queue_simulator.h"
//==============================================================================
// QueueSimulatorTest Class
// Description: This class defines the test fixture for the QueueSimulator
//              class. It sets up the testing environment and includes all the
//              test cases for the QueueSimulator class.
//==============================================================================
class QueueSimulatorTest : public ::testing::Test {
protected:
    QueueSimulator simulator;
    std::streambuf* originalCin;
    std::streambuf* originalCout;
    std::istringstream simulatedInput;
    std::ostringstream simulatedOutput;

    void SetUp() override {
        originalCin = std::cin.rdbuf();
        originalCout = std::cout.rdbuf();
    }

    void TearDown() override {
        std::cin.rdbuf(originalCin);
        std::cout.rdbuf(originalCout);
    }

    void simulateInput(const std::string& input) {
        simulatedInput = std::istringstream(input);
        std::cin.rdbuf(simulatedInput.rdbuf());
    }

    std::string getSimulatedOutput() {
        return simulatedOutput.str();
    }

    void captureOutput() {
        simulatedOutput.clear();
        simulatedOutput.str("");
        std::cout.rdbuf(simulatedOutput.rdbuf());
    }
};
//==============================================================================
// Test Cases
//==============================================================================
TEST_F(QueueSimulatorTest, AddCustomerTest) {
    simulateInput("John\n");
    captureOutput();
    simulator.addCustomer();
    std::string output = getSimulatedOutput();
    EXPECT_TRUE(output.find("John") != std::string::npos);
    EXPECT_TRUE(output.find("added to the queue") != std::string::npos);
}

TEST_F(QueueSimulatorTest, CallNextCustomerNotEmptyQueueTest) {
    simulateInput("John\n");
    simulator.addCustomer();
    captureOutput();
    simulator.callNextCustomer();
    std::string output = getSimulatedOutput();
    EXPECT_TRUE(output.find("Next customer") != std::string::npos);
    EXPECT_TRUE(output.find("John") != std::string::npos);
}

TEST_F(QueueSimulatorTest, CallNextCustomerEmptyQueueTest) {
    captureOutput();
    simulator.callNextCustomer();
    std::string output = getSimulatedOutput();
    EXPECT_TRUE(output.find("No customers in the queue") != std::string::npos);
}