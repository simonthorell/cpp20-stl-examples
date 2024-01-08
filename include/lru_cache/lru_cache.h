#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>
#include "lru_cache/hockey_player.h"
//=============================================================================
// Class: LRUCache
// Description: A cache for storing hockey players with an LRU eviction
//              policy. It combines a hash map and a doubly linked list. The
//              hash map (unordered_map) maps player's id to a pair of player
//              pointer and list iterator. The doubly linked list (std::list)
//              tracks the usage order, with the most recently used player at
//              the front and the least recently used at the back. When the
//              cache reaches its capacity, the least recently used player is
//              removed.
//=============================================================================
template <typename T>
class LRUCache {
    int capacity;
    std::list<int> lruList; // Store keys of cache
    std::unordered_map<int, std::pair<T*, typename std::list<int>::iterator>> cacheMap;

public:
//=============================================================================
// Constructor & Destructor: LRUCache
// Parameters: capacity - size of cache
// Description: Constructor for LRUCache. Initializes the cache with the given
//              capacity.
//              Destructor for LRUCache. Deletes/clears the cache.
//=============================================================================
    LRUCache(int capacity) : capacity(capacity) {}

    ~LRUCache() {
        for (auto &pair : cacheMap) {
            delete pair.second.first;
        }
    }
//=============================================================================
// Method: getPlayer
// Parameters: id - id of player to get
// Description: Returns the player with the given id if it exists in the cache.
//              Otherwise, returns nullptr.
//=============================================================================
    T* getPlayer(int id) {
        auto it = cacheMap.find(id);
        if (it == cacheMap.end()) return nullptr;
        // Move accessed player to the front of the list
        lruList.erase(it->second.second);
        lruList.push_front(id);
        it->second.second = lruList.begin();
        return it->second.first;
    }

    T* getPlayerWithoutUpdatingLRU(int id) {
        auto it = cacheMap.find(id);
        if (it == cacheMap.end()) return nullptr;
        return it->second.first;
    }
//=============================================================================
// Method: refer
// Parameters: id - id of player to add to cache
//             player - pointer to player to add to cache
// Description: Adds the given player to the cache. If the cache is full, the
//              least recently used player is removed from the cache.
//=============================================================================
    void refer(int id, T* player) {
        auto it = cacheMap.find(id);
        if (it != cacheMap.end()) {
            // Player is in cache, update LRU list
            lruList.erase(it->second.second);
        } else if (lruList.size() == capacity) {
            // Cache is full, remove LRU player
            int lru = lruList.back();
            lruList.pop_back();
            delete cacheMap[lru].first;
            cacheMap.erase(lru);
        }
        // Add new or recently accessed player to the front
        lruList.push_front(id);
        cacheMap[id] = {player, lruList.begin()};
    }
//=============================================================================
// Methods: isEmpty, getLRUList
// Description: Returns true if the cache is empty, false otherwise.
//              Returns the LRU list.
//=============================================================================
    bool isEmpty() const {
        return lruList.empty();
    }

    const std::list<int>& getLRUList() const {
        return lruList;
    }
};

//=============================================================================
// Template Instantiation
//=============================================================================
template class LRUCache<HockeyPlayer>;

#endif // LRU_CACHE_H