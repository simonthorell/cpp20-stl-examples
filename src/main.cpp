#include "sensor_data/sensor_data.h"
#include "queue_simulator/queue_simulator.h"
#include "atm_simulator/atm_simulator.h"
#include "lru_cache/lru_cache.h"
#include <iostream> // std::cout, std::cin

void displayMenu() {
    std::cout << "================== Menu ==================\n";
    std::cout << "1. Part 1 - Sensor Data (Altitude)\n";
    std::cout << "2. Part 2 - Sensor Data (Speed)\n";
    std::cout << "3. Part 3 - Sensor Data (Fuel Consumption)\n";
    std::cout << "4. Part 4 - Queue Simulator\n";
    std::cout << "5. Part 5 - ATM Simulator\n";
    std::cout << "6. Part 6 - LRU Cache\n";
    std::cout << "7. Exit\n";
    std::cout << "==========================================\n";
    std::cout << "Select an option (1-4): ";
}

int main() {
    int choice;
    bool exit = false;

    while (!exit) {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            sensor_data();
            break;
        case 2:
            sensor_data();
            break;
        case 3:
            sensor_data();
            break;
        case 4:
            queue_simulator();
            break;
        case 5:
            atm_simulator();
            break;
        case 6:
            lru_cache();
            break;
        case 7:
            exit = true;
            break;
        default:
            std::cout << "Invalid selection. Please try again.\n";
        }
    }

    return EXIT_SUCCESS;
}