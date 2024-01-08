#ifndef HOCKEY_APP_H
#define HOCKEY_APP_H

#include <string>
#include "lru_cache/lru_cache.h"

class HockeyApp {
public:
    // Constructor
    HockeyApp(int cacheSize, int amountOfPlayers, const std::string& filename);
    // Destructor
    ~HockeyApp();
    // Run the app
    void run();
private:
    LRUCache<HockeyPlayer>* cache; // Cache of HockeyPlayers
    std::string filename; // Name of file to load players from
public: // Make public for testing purposes
    // Class Data Methods
    void generateRandomPlayers(int amountOfPlayers); // Generate random players and save to file
    void populateCacheWithPlayersFromFile(int chacheSize); // Populate cache with players
    HockeyPlayer* loadPlayerFromFile(int id); // Load player from file
    HockeyPlayer parsePlayerLine(const std::string& line); // Parse player from line
    // Class UI methods
    void printMenu();            // Print menu
    void showPlayersInCache();   // Show players in cache
    void searchPlayerByID();     // Search player by ID
};

#endif // HOCKEYAPP_H