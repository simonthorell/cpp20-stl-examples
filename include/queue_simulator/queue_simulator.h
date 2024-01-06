#ifndef QUEUE_SIMULATOR_H
#define QUEUE_SIMULATOR_H

#include <queue>
#include "queue_simulator/customer.h"

class QueueSimulator {
public:
    // Constructor
    QueueSimulator();
    // Method to run the queue simulator
    char Run();
private:
    std::queue<Customer> queue;  // Queue of customers waiting for service.
    int nextQueueNumber;         // The number to assign to the next customer.
    // Class private methods
    void AddCustomer();
    void CallNextCustomer();
};

#endif // QUEUE_SIMULATOR_H
