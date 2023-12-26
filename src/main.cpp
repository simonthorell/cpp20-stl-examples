/******************************************************************************
 * File Name: main.cpp
 * Project Name: cpp-Iot23-algorithms
 * Author: Simon Thorell
 * Date Created: 2023-12-26
 * Last Modified: 2023-12-26
 * Description: This file contains the main execution loop for the exam in the
 *              course 'Datastructures and Algorithms' for IoT23 at Nackademin,
 *              Stockholm, Sweden. It initializes the system and manages the 
 *              main application lifecycle.
 * License: MIT License
 ******************************************************************************/

// Include standard libraries
#include <iostream> // std::cout, std::cin

// Include header files
#include "sensor_data/sensor_data.h"
#include "queue_simulator/queue_simulator.h"
#include "atm_simulator/atm_simulator.h"
#include "lru_cache/lru_cache.h"

// Declare utility functions
void displayMenu();
int runMenuLoop();

//=============================================================================
//                                Main Function
//=============================================================================

int main() {
    if (!runMenuLoop())
        return EXIT_SUCCESS; // runMenuLoop() exited successfully (0)
    else
        return EXIT_FAILURE; // runMenuLoop() exited with failure (1)
}

//=============================================================================
//                              Utility Functions
//=============================================================================

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

int runMenuLoop() {
    char exec = 0; // 0 = success, 1 = failure
    char choice;
    bool exit = false;

    while (!exit) {
        if (exec > 0) // check if previous execution failed
            std::cout << "Execution failed!\n";

        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            exec = sensor_data();
            break;
        case '2':
            exec = sensor_data();
            break;
        case '3':
            exec = sensor_data();
            break;
        case '4':
            exec = queue_simulator();
            break;
        case '5':
            exec = atm_simulator();
            break;
        case '6':
            exec = lru_cache();
            break;
        case '7':
            exit = true;
            break;
        default:
            std::cout << "Invalid selection. Please try again.\n";
        }
    }
    // Return 0 if exited successfully using 'exit', otherwise return 1
    return exit ? 0 : 1;
}