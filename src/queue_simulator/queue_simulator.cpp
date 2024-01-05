#include <iostream>
#include "queue_simulator/queue_simulator.h"

//=============================================================================
// Constructor: QueueSimulator
// Description: Initializes the next queue number to 1 for the queue simulator.
//=============================================================================
QueueSimulator::QueueSimulator() : nextQueueNumber(1) {}

//=============================================================================
// Function: Run
// Description: Runs the main loop of the queue simulator, processing user
//              commands to manage the queue of customers.
//=============================================================================
char QueueSimulator::Run() {
    std::string input;
    while (true) {
        std::cout << "Enter 'new' to add a new customer or 'next' to call the "
                     "next customer ('exit' to exit): ";
        std::cin >> input;

        if (input == "new") {
            AddCustomer();
        } else if (input == "next") {
            CallNextCustomer();
        } else if (input == "exit") {
            break; // Exit the loop and end the program.
        } else {
            std::cout << "Invalid input. Please enter 'new', 'next', or 'exit'.\n";
        }
    }
    return 0;
}

//=============================================================================
// Function: AddCustomer
// Description: Adds a new customer to the queue with a unique number and
//              reads the customer's name from the input.
//=============================================================================
void QueueSimulator::AddCustomer() {
    std::string name;
    std::cout << "Enter customer name: ";
    std::cin >> name;
    Customer newCustomer(nextQueueNumber++, name);
    queue.push(newCustomer);
    std::cout << "Customer " << name << " added to the queue with number " 
              << newCustomer.queueNumber << ".\n";
}

//=============================================================================
// Function: CallNextCustomer
// Description: Calls and removes the next customer from the queue, calculating
//              and displaying their wait time.
//=============================================================================
void QueueSimulator::CallNextCustomer() {
    if (!queue.empty()) {
        Customer nextCustomer = queue.front();
        queue.pop();
        time_t currentTime;
        time(&currentTime);
        double waitTime = difftime(currentTime, nextCustomer.arrivalTime);
        std::cout << "Next customer (" << nextCustomer.name << ") has been "
                     "waiting for " << waitTime << " seconds.\n";
    } else {
        std::cout << "No customers in the queue.\n";
    }
}
