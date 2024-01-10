/******************************************************************************
 * File Name: main.cpp
 * Project Name: cpp-Iot23-algorithms
 * Author: Simon Thorell
 * Date Created: 2023-12-26
 * Last Modified: 2023-01-03
 * Description: This file contains the main execution loop for the exam in the
 *              course 'Datastructures and Algorithms' for IoT23 at Nackademin,
 *              Stockholm, Sweden. 
 ******************************************************************************/
// Include standard libraries
#include <iostream> // std::cout, std::cin
// Include header files
#include "sensor_data/sensor_data.h"
#include "queue_simulator/queue_simulator.h"
#include "atm_simulator/atm_simulator.h"
#include "lru_cache/hockey_app.h"
// Declare utility functions
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
            case 1: sensorData(1); break;
            case 2: sensorData(2); break;
            case 3: sensorData(3); break;
            case 4: QueueSimulator().run(); break;
            case 5: {
                auto manager = std::make_shared<AccountManager>();
                ATMSimulator(manager).run(); 
                break;
            }
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