#ifndef HOCKEY_APP_H
#define HOCKEY_APP_H

#include <string>
#include <unordered_map>
#include <vector>
#include "lru_cache/lru_cache.h"

class HockeyApp {
public:
    // Constructor
    HockeyApp(int cacheSize, const std::string& filename);
    // Destructor
    ~HockeyApp();
    // Run the app
    void run();
private:
    LRUCache<HockeyPlayer>* cache; // Cache of HockeyPlayers
    std::unordered_map<int, HockeyPlayer> allPlayers; // Map of all players
    std::string filename; // Name of file to load players from
public: // Make public for testing purposes
    // Class Data Methods
    void generateRandomPlayers(); // Generate random players and save to file
    void populateCacheWithRandomPlayers(); // Populate cache with random players
    void loadPlayersFromFile(); // Load players from file into allPlayers map
    HockeyPlayer parsePlayerLine(const std::string& line); // Parse player from line
    // Class UI methods
    void printMenu();            // Print menu
    void showPlayersInCache();   // Show players in cache
    void searchPlayerByID();     // Search player by ID
    void searchPlayerByName();   // Search player by name
    void searchPlayerByJersey(); // Search player by jersey number
};

#endif // HOCKEYAPP_H