#ifndef QUEUE_SIMULATOR_H
#define QUEUE_SIMULATOR_H

#include <queue>
#include "queue_simulator/customer.h"

//=============================================================================
// Class: QueueSimulator
// Description: Manages a queue of customers. Allows adding new customers to the
//              queue, calling the next customer, and running the main loop of
//              the simulator.
//=============================================================================
class QueueSimulator {
public:
    //=========================================================================
    // Constructor: QueueSimulator
    // Description: Initializes the QueueSimulator with the next queue number
    //              set to 1.
    //=========================================================================
    QueueSimulator();

    //=========================================================================
    // Function: Run
    // Description: Runs the main loop of the queue simulator, processing user
    //              commands to manage the queue of customers. Returns the
    //              status of the program.
    //=========================================================================
    char Run();

private:
    std::queue<Customer> queue;  // Queue of customers waiting for service.
    int nextQueueNumber;         // The number to assign to the next customer.

    //=========================================================================
    // Function: AddCustomer
    // Description: Prompts for a customer's name and adds them to the queue
    //              with a unique number.
    //=========================================================================
    void AddCustomer();

    //=========================================================================
    // Function: CallNextCustomer
    // Description: Calls and removes the next customer from the queue,
    //              calculating and displaying their wait time.
    //=========================================================================
    void CallNextCustomer();
};

#endif // QUEUE_SIMULATOR_H
