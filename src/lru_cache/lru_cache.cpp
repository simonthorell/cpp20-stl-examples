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
    if (cacheMap.find(id) == cacheMap.end())
        return nullptr;
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
void LRUCache<T>::refer(int id, T* player) {
    if (cacheMap.find(id) == cacheMap.end()) {
        if (lruList.size() == capacity) {
            int last = lruList.back();
            lruList.pop_back();
            delete cacheMap[last].first;
            cacheMap.erase(last);
        }
    } else {
        lruList.erase(cacheMap[id].second);
    }
    lruList.push_front(id);
    cacheMap[id] = {player, lruList.begin()};
}
//=============================================================================
// Explicit template instantiation
// Description: Explicitly instantiates the LRUCache class for HockeyPlayer.
//=============================================================================
template class LRUCache<HockeyPlayer>;