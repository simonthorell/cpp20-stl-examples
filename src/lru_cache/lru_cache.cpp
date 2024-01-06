#include "lru_cache/lru_cache.h"
//=============================================================================
// Constructor & Destructor: LRUCache
// Parameters: capacity - size of cache
// Description: Constructor for LRUCache. Initializes the cache with the given
//              capacity.
//              Destructor for LRUCache. Deletes/clears the cache.
//=============================================================================
template <typename T> // Constructor
LRUCache<T>::LRUCache(int capacity) : capacity(capacity) {}

template <typename T> // Destructor
LRUCache<T>::~LRUCache() {
    // Delete all players in the cache
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
template <typename T>
T* LRUCache<T>::getPlayer(int id) {
    // If the player is not in the cache, return nullptr
    if (cacheMap.find(id) == cacheMap.end())
        return nullptr;
    // Otherwise, move the player to the front of the list and return it
    refer(id, cacheMap[id].first);
    return cacheMap[id].first;
}
//=============================================================================
// Method: refer
// Parameters: id - id of player to add to cache
//             player - pointer to player to add to cache
// Description: Adds the given player to the cache. If the cache is full, the
//              least recently used player is removed from the cache.
//=============================================================================
template <typename T>
// Add the given player to the cache
void LRUCache<T>::refer(int id, T* player) {
    // If the player is not in the cache
    if (cacheMap.find(id) == cacheMap.end()) {
        // If the cache is full, remove the least recently used player
        if (lruList.size() == capacity) {
            // Get the id of the least recently used player
            int last = lruList.back();
            // Remove the player from the cache
            lruList.pop_back();
            // Delete the player from the heap
            delete cacheMap[last].first;
            // Remove the player from the cache map
            cacheMap.erase(last);
        }
    // If the player is in the cache, remove it from the list
    } else {
        lruList.erase(cacheMap[id].second);
    }
    // Add the player to the front of the list and cache map
    lruList.push_front(id);
    // Add the player to the cache map
    cacheMap[id] = {player, lruList.begin()};
}
//=============================================================================
// Explicit template instantiation
// Description: Explicitly instantiates the LRUCache class for HockeyPlayer.
//=============================================================================
template class LRUCache<HockeyPlayer>;