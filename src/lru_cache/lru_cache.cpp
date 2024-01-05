#include "lru_cache/lru_cache.h"
#include <iostream>

//==============================================================================
// Constructor
//==============================================================================

LRUCache::LRUCache(int capacity) : capacity(capacity) {}

//==============================================================================
// Public Methods
//==============================================================================

int LRUCache::Run() {
    // TODO: Implement user interface
    std::cout << "LRU Cache Simulator" << std::endl;
    return 0;
}

//==============================================================================
// Private Methods
//==============================================================================

const HockeyPlayer* LRUCache::getPlayer(int id) {
    if (cacheMap.find(id) != cacheMap.end()) {
        // Player is in cache, move it to the front
        auto it = cacheMap[id];
        cache.splice(cache.begin(), cache, it);
        return &(*it);
    } else {
        // Player not in cache, read from file (simulated) and add to cache
        HockeyPlayer player(id, "PlayerName", 88, "TeamName");
        addToCache(player);
        return &cache.front();
    }
}

void LRUCache::addToCache(const HockeyPlayer& player) {
    if (cache.size() >= capacity) {
        // Remove the least recently used player
        cacheMap.erase(cache.back().getId());
        cache.pop_back();
    }
    cache.push_front(player);
    cacheMap[player.getId()] = cache.begin();
}