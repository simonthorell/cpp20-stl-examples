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
    std::string filename; // Name of players file
public: // Make public for testing purposes
    // Class Data Methods
    void generateRandomPlayersFile(int amountOfPlayers);
    void populateCacheWithCurrentNHLSpotlightPlayers(int cacheSize);
    // void populateCacheWithPlayersFromFile(int chacheSize);
    HockeyPlayer* loadPlayerFromFile(int id);
    HockeyPlayer parsePlayerLine(const std::string& line);
    HockeyPlayer* findPlayerInCacheByName(const std::string& name);
    // Class UI methods
    void printMenu();
    void showPlayersInCache();
    void searchPlayerByID();
    void searchPlayerByName(int searchLimit);
};

#endif // HOCKEYAPP_H