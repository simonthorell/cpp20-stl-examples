#ifndef HOCKEY_APP_H
#define HOCKEY_APP_H

#include "lru_cache/lru_cache.h"
#include <string>
#include <unordered_map>
#include <vector>

class HockeyApp {
    LRUCache<HockeyPlayer>* cache;
    std::unordered_map<int, HockeyPlayer> allPlayers;
    std::string filename;

    void generateRandomPlayers();
    void populateCacheWithRandomPlayers();
    void loadPlayersFromFile();
    HockeyPlayer parsePlayerLine(const std::string& line);
    void printMenu();
    void showPlayersInCache();
    void searchPlayerByID();
    void searchPlayerByName();
    void searchPlayerByJersey();

public:
    HockeyApp(int cacheSize, const std::string& filename);
    ~HockeyApp();
    void run();
};

#endif // HOCKEYAPP_H