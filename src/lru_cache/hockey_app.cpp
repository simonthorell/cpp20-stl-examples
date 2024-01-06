#include "lru_cache/hockey_app.h"
#include <fstream>
#include <random>
#include <iostream>
#include <sstream>
#include <filesystem>

//=============================================================================
// Constructor & Destructor: HockeyApp
// Parameters: cacheSize - size of cache
//             filename - name of file to load players from
//=============================================================================
HockeyApp::HockeyApp(int cacheSize, const std::string& filename)
    : cache(new LRUCache<HockeyPlayer>(cacheSize)), filename(filename) {
    if (!std::filesystem::exists(filename)) {
        generateRandomPlayers();
    }
    loadPlayersFromFile();
}

HockeyApp::~HockeyApp() {
    delete cache;
}
//=============================================================================
// Method: generateRandomPlayers
// Description: Generates 100,000 random hockey players and saves them to file.
//=============================================================================
void HockeyApp::generateRandomPlayers() {
    std::ofstream file(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 99);
    std::uniform_int_distribution<> disId(1, 100000);
    for (int i = 0; i < 100000; ++i) {
        file << disId(gen) << ",Player" << i << "," << dis(gen) << ",Team" 
            << dis(gen) << std::endl;
    }
    std::cout << "Generated " << 100000 << " random hockey players in file: "
              << filename << std::endl;
}
//=============================================================================
// Methods: loadPlayersFromFile, parsePlayerLine
// Description: Loads players from file into allPlayers map then parse them.
//=============================================================================
void HockeyApp::loadPlayersFromFile() {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        HockeyPlayer player = parsePlayerLine(line);
        allPlayers[player.id] = player;
    }
}

HockeyPlayer HockeyApp::parsePlayerLine(const std::string& line) {
    std::istringstream iss(line);
    int id, jersey;
    std::string name, teamName;
    char delim;

    iss >> id >> delim >> name >> delim >> jersey >> delim >> teamName;
    return HockeyPlayer(id, name, jersey, teamName);
}
//=============================================================================
// Methods: printMenu, showPlayersInCache, searchPlayerByID, searchPlayerByName,
//          searchPlayerByJersey
// Description: User interface methods for the HockeyApp.
//=============================================================================
void HockeyApp::printMenu() {
    std::cout << "\n=== Hockey Player App Menu ===\n";
    std::cout << "1. Show Players in Cache\n";
    std::cout << "2. Search Player by ID\n";
    std::cout << "3. Search Player by Name\n";
    std::cout << "4. Search Player by Jersey Number\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
}

void HockeyApp::showPlayersInCache() {
    std::cout << "\n-- Players in Cache --\n";
    // Implement showing players in cache
}

void HockeyApp::searchPlayerByID() {
    int id;
    std::cout << "Enter Player ID: ";
    std::cin >> id;
    HockeyPlayer* player = cache->getPlayer(id);
    if (player) {
        std::cout << "Player found in cache: " << player->name << std::endl;
    } else if (allPlayers.find(id) != allPlayers.end()) {
        std::cout << "Player found in file: " << allPlayers[id].name << std::endl;
        // Consider adding player to cache here
    } else {
        std::cout << "Player not found." << std::endl;
    }
}

void HockeyApp::searchPlayerByName() {
    std::string name;
    std::cout << "Enter Player Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    // Implement search by name
}

void HockeyApp::searchPlayerByJersey() {
    int jersey;
    std::cout << "Enter Jersey Number: ";
    std::cin >> jersey;
    // Implement search by jersey number
}
//=============================================================================
// Method: run
// Description: Runs the HockeyApp.
//=============================================================================
void HockeyApp::run() {
    int choice;
    do {
        printMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: showPlayersInCache(); break;
            case 2: searchPlayerByID(); break;
            case 3: searchPlayerByName(); break;
            case 4: searchPlayerByJersey(); break;
            case 5: break;
            default: std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);
}
