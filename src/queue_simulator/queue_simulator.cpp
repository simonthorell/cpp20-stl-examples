#include <iostream>
#include <queue>
#include "queue_simulator/queue_simulator.h"
#include "queue_simulator/customer.h"

int queue_simulator() {
    std::queue<Customer> queue;
    int nextQueueNumber = 1;
    std::string input;

    while (true) {
        std::cout << "Enter 'new' to add a new customer or 'next' to call the next customer: ";
        std::cin >> input;

        if (input == "new") {
            // Add new customer
            std::string name;
            std::cout << "Enter customer name: ";
            std::cin >> name;
            Customer newCustomer(nextQueueNumber++, name);
            queue.push(newCustomer);
            std::cout << "Customer " << name << " added to the queue with number " << newCustomer.queueNumber << ".\n";
        } else if (input == "next" && !queue.empty()) {
            // Call next customer
            Customer nextCustomer = queue.front();
            queue.pop();
            time_t currentTime;
            time(&currentTime);
            double waitTime = difftime(currentTime, nextCustomer.arrivalTime);
            std::cout << "Next customer (" << nextCustomer.name << ") has been waiting for " << waitTime << " seconds.\n";
        } else if (input == "next" && queue.empty()) {
            std::cout << "No customers in the queue.\n";
        } else if (input == "stop") {
            break; // Exit the loop and end the program.
        } else {
            std::cout << "Invalid input. Please enter 'new', 'next', or 'stop'.\n";
        }
    }
    return 0;
}