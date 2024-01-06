#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>
#include "lru_cache/hockey_player.h"

class LRUCache {
public:
    LRUCache(int capacity);
    const HockeyPlayer* getPlayer(int id);

    int Run();

private:
    int capacity;
    std::list<HockeyPlayer> cache;
    std::unordered_map<int, std::list<HockeyPlayer>::iterator> cacheMap;
    
    void addToCache(const HockeyPlayer& player);
};


#endif // LRU_CACHE_H