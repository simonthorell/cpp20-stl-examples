// Customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ctime>

class Customer {
public:
    int queueNumber;
    std::string name;
    time_t arrivalTime;

    Customer(int num, std::string n);
};

#endif //CUSTOMER_H
