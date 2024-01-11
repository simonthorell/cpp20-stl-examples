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
    // Class methods (public for testing)
    void addCustomer();
    void callNextCustomer();
private:
    std::queue<Customer> queue;  // Queue of customers waiting for service.
    int nextQueueNumber;         // The number to assign to the next customer.
};

#endif // QUEUE_SIMULATOR_H
