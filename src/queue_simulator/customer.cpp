// Customer.cpp
#include "queue_simulator/customer.h"

Customer::Customer(int num, std::string n) {
    queueNumber = num;
    name = n;
    time(&arrivalTime); // Capture the current time as arrival time.
}
