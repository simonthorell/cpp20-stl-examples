#include "lru_cache/hockey_app.h"
#include <fstream>
#include <random>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <deque>
//=============================================================================
// Constructor & Destructor: HockeyApp
// Parameters: cacheSize - size of cache
//             filename - name of file to load players from
// Description: Constructor generates random players if the file does not exist.
//              Populates the cache with "cacheSize" random players.
//              Destructor for HockeyApp. Deletes/clears the cache.
//=============================================================================
HockeyApp::HockeyApp(int cacheSize, int amountOfPlayers, const std::string& filename)
    // Initialize cache and filename
    : cache(new LRUCache<HockeyPlayer>(cacheSize)), filename(filename) {
    // Generate random players file - if the file does not exist
    if (!std::filesystem::exists(filename)) {
        // Generate 'amountOfPlayers' random players and save them to file
        generateRandomPlayers(amountOfPlayers);
    }
    // Populate the LRU cache with 'cacheSize' amount of players
    populateCacheWithPlayersFromFile(cacheSize);
}

HockeyApp::~HockeyApp() {
    delete cache; // clear the cache on destruction
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
            case 0: break;
            default: std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);
}
//=============================================================================
// Method: generateRandomPlayers
// Description: Generates 100,000 random hockey players and saves them to file.
//=============================================================================
void HockeyApp::generateRandomPlayers(int amountOfPlayers) {
    std::ofstream file(filename); // Open file for writing (filename from variable)
    std::random_device rd;      // Obtain a random number from hardware
    std::mt19937 gen(rd());     // Random number generator
    std::uniform_int_distribution<> dis(1, 99); // Jersey & Team no. range

    for (int i = 0; i < amountOfPlayers; ++i) {
        // Assign a unique ID (i) to each player
        file << i << ",Player" << i << "," << dis(gen) << ",Team" 
            << dis(gen) << std::endl;
    }
    std::cout << "Generated " << amountOfPlayers << " random hockey players in file: "
              << filename << std::endl;
}
//=============================================================================
// Method: populateCacheWithPlayersFromFile
// Description: Populates the cache with "cacheSize" random players.
//=============================================================================
void HockeyApp::populateCacheWithPlayersFromFile(int cacheSize) {
    std::ifstream file(filename);
    std::string line;
    std::deque<HockeyPlayer> recentPlayers;

    // Get the last (newest) 10 players in the file
    while (std::getline(file, line)) {
        HockeyPlayer player = parsePlayerLine(line);
        recentPlayers.push_back(player);
        // If we have more than cacheSize players, remove the oldest one
        if (recentPlayers.size() > cacheSize) {
            recentPlayers.pop_front();
        }
    }

    // Populate the cache with the players
    for (const HockeyPlayer& player : recentPlayers) {
        cache->refer(player.id, new HockeyPlayer(player));
    }

    std::cout << "Populated cache with " << recentPlayers.size() 
              << " (up to 10) recent players from the file." << std::endl;
}
// Alternative implementation (First 10 players in file):
// void HockeyApp::populateCacheWithPlayersFromFile(int cacheSize) {
//     std::ifstream file(filename);
//     std::string line;
//     int count = 0;
//     while (std::getline(file, line) && count < cacheSize) {
//         HockeyPlayer player = parsePlayerLine(line);
//         cache->refer(player.id, new HockeyPlayer(player));
//         ++count;
//     }
//     std::cout << "Populated cache with 10 random players from the file." 
//               << std::endl;
// }
//=============================================================================
// Methods: loadPlayersFromFile, parsePlayerLine
// Description: Loads players from file into allPlayers map then parse them.
//=============================================================================
HockeyPlayer* HockeyApp::loadPlayerFromFile(int id) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        HockeyPlayer player = parsePlayerLine(line);
        if (player.id == id) {
            return new HockeyPlayer(player);
        }
    }
    return nullptr; // Return null if player not found
}

HockeyPlayer HockeyApp::parsePlayerLine(const std::string& line) {
    std::istringstream iss(line); // String stream to parse the line
    int id, jersey;               // Integers to hold the ID and jersey number 
    std::string name, teamName;   // Strings to hold the name and team name
    char delim;                   // Character to hold the delimiter (,)

    iss >> id >> delim;           // Read the ID and the delimiter (,)
    std::getline(iss, name, ','); // Read the name up to the next comma
    iss >> jersey >> delim;  // Read the jersey number and the next delimiter
    std::getline(iss, teamName);  // Read the rest of the line as the team name

    return HockeyPlayer(id, name, jersey, teamName);
}
//=============================================================================
// Methods: printMenu, showPlayersInCache, searchPlayerByID, searchPlayerByName
// Description: User interface methods for the HockeyApp.
//=============================================================================
void HockeyApp::printMenu() {
    std::cout << "\n===== Hockey Player App Menu =====\n";
    std::cout << "1. Show Players in Cache\n";
    std::cout << "2. Search Player by ID\n";
    std::cout << "0. Exit\n";
    std::cout << "==================================\n";
    std::cout << "Select an option: ";
}

void HockeyApp::showPlayersInCache() {
    std::cout << "\n-- Players in Cache --\n";

    if (cache->isEmpty()) {
        std::cout << "Cache is empty.\n";
        return;
    }

    int count = 0; // Keep track of how many players are in the cache
    for (const int id : cache->getLRUList()) {
        HockeyPlayer* player = cache->getPlayerWithoutUpdatingLRU(id);
        if (player) {
            std::cout << "Cache Entry " << ++count << ":\tID: " << player->id 
                      << ", Name: " << player->name << ", Jersey: " 
                      << player->jersey << ", Team: " << player->teamName 
                      << "\n";
        }
    }
}

void HockeyApp::searchPlayerByID() {
    int id;
    std::cout << "Enter Player ID: ";
    if (!(std::cin >> id) || id < 0) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        std::cout << "Invalid ID entered. Please enter a positive number.\n";
        return;
    }

    HockeyPlayer* player = cache->getPlayer(id);
    if (player) {
        std::cout << "Player found in cache: " << player->name << std::endl;
        cache->refer(id, player);  // Update LRU position
    } else {
        try {
            player = loadPlayerFromFile(id);
            if (player) {
                std::cout << "Player found in file: " << player->name << std::endl;
                cache->refer(id, player);
                std::cout << "Player added to cache." << std::endl;
            } else {
                std::cout << "Player with ID: " << id << " not found." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Failed to load player from file: " << e.what() << std::endl;
        }
    }
}