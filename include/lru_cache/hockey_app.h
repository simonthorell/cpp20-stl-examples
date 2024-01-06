#ifndef HOCKEY_APP_H
#define HOCKEY_APP_H

#include "lru_cache/lru_cache.h"
#include <string>

class HockeyApp {
    LRUCache<HockeyPlayer>* cache;
    std::string filename;

public:
    HockeyApp(int cacheSize, const std::string& filename);
    ~HockeyApp();
    void generateRandomPlayers();
    void run();
};

#endif // HOCKEYAPP_H