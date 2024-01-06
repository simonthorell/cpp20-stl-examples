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
// Description: Constructor generates random players if the file does not exist.
//              Populates the cache with "cacheSize" random players.
//              Destructor for HockeyApp. Deletes/clears the cache.
//=============================================================================
HockeyApp::HockeyApp(int cacheSize, const std::string& filename)
    // Initialize cache and filename
    : cache(new LRUCache<HockeyPlayer>(cacheSize)), filename(filename) {
    // Generate random players if the file does not exist
    if (!std::filesystem::exists(filename)) {
        generateRandomPlayers();
    }
    // Load players from file into allPlayers map. (Maybe remove later..!)
    loadPlayersFromFile(); // TODO: Maybe do this lazily/read direct from file?
    // Populate the cache with random players
    populateCacheWithRandomPlayers();
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
            case 3: searchPlayerByName(); break;
            case 4: searchPlayerByJersey(); break;
            case 0: break;
            default: std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);
}
//=============================================================================
// Method: generateRandomPlayers
// Description: Generates 100,000 random hockey players and saves them to file.
//=============================================================================
void HockeyApp::generateRandomPlayers() {
    std::ofstream file(filename); // Open file for writing (filename from variable)
    std::random_device rd;      // Obtain a random number from hardware
    std::mt19937 gen(rd());     // Random number generator
    std::uniform_int_distribution<> dis(1, 99); // Jersey & Team no. range
    std::uniform_int_distribution<> disId(1, 100000); // ID range
    for (int i = 0; i < 100000; ++i) {
        file << disId(gen) << ",Player" << i << "," << dis(gen) << ",Team" 
            << dis(gen) << std::endl;
    }
    std::cout << "Generated " << 100000 << " random hockey players in file: "
              << filename << std::endl;
}
//=============================================================================
// Method: populateCacheWithRandomPlayers
// Description: Populates the cache with "cacheSize" random players.
//=============================================================================
void HockeyApp::populateCacheWithRandomPlayers() {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Random number generator
    // Uniform distribution of integers from 0 to size of allPlayers map - 1
    std::uniform_int_distribution<> dis(0, allPlayers.size() - 1);

    std::vector<int> keys; // Vector of all keys in allPlayers map
    // Populate the vector with all keys in allPlayers map
    for (const auto& pair : allPlayers) {
        keys.push_back(pair.first);
    }
    // Populate the cache with 10 random players
    for (int i = 0; i < 10; ++i) {
        int randomIndex = dis(gen);  // Get a random index
        int key = keys[randomIndex]; // Get the key at that index
        HockeyPlayer player = allPlayers[key];
        cache->refer(key, new HockeyPlayer(player.id, player.name, 
                                           player.jersey, player.teamName));
    }
    std::cout << "Populated cache with 10 random players from the file." 
              << std::endl;
}
//=============================================================================
// Methods: loadPlayersFromFile, parsePlayerLine
// Description: Loads players from file into allPlayers map then parse them.
//=============================================================================
void HockeyApp::loadPlayersFromFile() {
    std::ifstream file(filename); // Open file for reading (filename from variable)
    std::string line;           // String to hold each line of the file
    // Read each line of the file
    while (std::getline(file, line)) {
        HockeyPlayer player = parsePlayerLine(line);
        allPlayers[player.id] = player;
    }
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
// Methods: printMenu, showPlayersInCache, searchPlayerByID, searchPlayerByName,
//          searchPlayerByJersey
// Description: User interface methods for the HockeyApp.
//=============================================================================
void HockeyApp::printMenu() {
    std::cout << "\n===== Hockey Player App Menu =====\n";
    std::cout << "1. Show Players in Cache\n";
    std::cout << "2. Search Player by ID\n";
    std::cout << "3. Search Player by Name\n";
    std::cout << "4. Search Player by Jersey Number\n";
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
        HockeyPlayer* player = cache->getPlayer(id);
        if (player) {
            std::cout << "Cache Entry " << ++count << ": ID: " << player->id 
                      << ", Name: " << player->name << ", Jersey: " 
                      << player->jersey << ", Team: " << player->teamName 
                      << "\n";
        }
    }
    // std::cout << "Total players in cache: " << count << "\n";
}

// TODO: Fix this bug!
void HockeyApp::searchPlayerByID() {
    int id;
    std::cout << "Enter Player ID: ";
    std::cin >> id;
    HockeyPlayer* player = cache->getPlayer(id);
    if (player) {
        std::cout << "Player found in cache: " << player->name << std::endl;
    } else if (allPlayers.find(id) != allPlayers.end()) {
        std::cout << "Player found in file: " << allPlayers[id].name << std::endl;
        // Create a copy of the player from the file
        HockeyPlayer filePlayer = allPlayers[id];
        // Dynamically allocate a new player 
        // (ensure cache is set up to manage this memory properly!)
        HockeyPlayer* newPlayer = new HockeyPlayer(filePlayer.id, filePlayer.name, 
                                                   filePlayer.jersey, 
                                                   filePlayer.teamName);
        // Add the new player to the cache
        cache->refer(id, newPlayer);

        std::cout << "Player added to cache." << std::endl;
    } else {
        std::cout << "Player not found." << std::endl;
    }
}

void HockeyApp::searchPlayerByName() {
    std::string name;
    std::cout << "Enter Player Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    // TODO: Implement search by name
}

void HockeyApp::searchPlayerByJersey() {
    int jersey;
    std::cout << "Enter Jersey Number: ";
    std::cin >> jersey;
    // TODO: Implement search by jersey number
}