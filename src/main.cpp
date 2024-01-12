/******************************************************************************
 * File Name: main.cpp
 * Project Name: cpp-Iot23-algorithms
 * Author: Simon Thorell
 * Date Created: 2023-12-26
 * Last Modified: 2024-01-10
 * Description: This project contains various algorithms and data structures
 *              implemented in C++. The purpose of this project is to practice
 *              and demonstrate understanding of algorithms & data structures.
 ******************************************************************************/
#include <iostream>

#include "sensor_data/sensor_data_manager.h"  // Sensor Data Processing
#include "queue_simulator/queue_simulator.h"  // Queue Simulator
#include "atm_simulator/atm_simulator.h"      // ATM Simulator
#include "lru_cache/hockey_app.h"             // LRU Cache
#include "lru_cache/nhl_api.h"            // LRU Cache

void displayMenu();
//=============================================================================
//                             Main Execution
//=============================================================================
int main() {
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: case 2: case 3:
                SensorDataManager(choice, 2012, 1, 2, 99.9f, 1.75f).run(); break;
            case 4: QueueSimulator().run(); break;
            case 5: ATMSimulator(std::make_shared<AccountManager>()).run(); break;
            case 6: HockeyApp(10,100000,"hockey_players.txt").run(); break;
        }
    } while (choice != 0); // Exit when user enters 0

    return EXIT_SUCCESS;
}
//=============================================================================
//                             Utility Functions
//=============================================================================
void displayMenu() {
    std::cout << "================== Menu ==================\n";
    std::cout << "1. Part 1 - Sensor Data (Altitude)\n";
    std::cout << "2. Part 2 - Sensor Data (Max Speed)\n";
    std::cout << "3. Part 3 - Sensor Data (Fuel Consumption)\n";
    std::cout << "4. Part 4 - Queue Simulator\n";
    std::cout << "5. Part 5 - ATM Simulator\n";
    std::cout << "6. Part 6 - LRU Cache\n";
    std::cout << "0. Exit\n";
    std::cout << "==========================================\n";
    std::cout << "Select an option (0-6): ";
}