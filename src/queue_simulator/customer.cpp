// Customer.cpp
#include "queue_simulator/customer.h"

//=============================================================================
// Constructor: Customer
// Description: Initializes the customer with the given queue number and name.
//=============================================================================
Customer::Customer(int num, std::string n) {
    queueNumber = num;
    name = n;
    time(&arrivalTime); // Capture the current time as arrival time.
}