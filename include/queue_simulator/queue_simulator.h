#ifndef QUEUE_SIMULATOR_H
#define QUEUE_SIMULATOR_H

#include <queue>
#include "queue_simulator/customer.h"

class QueueSimulator {
public:
    // Constructor
    QueueSimulator();
    // Method to run the queue simulator
    char run();
private:
    std::queue<Customer> queue;  // Queue of customers waiting for service.
    int nextQueueNumber;         // The number to assign to the next customer.
    // Class private methods
    void addCustomer();
    void callNextCustomer();
};

#endif // QUEUE_SIMULATOR_H
