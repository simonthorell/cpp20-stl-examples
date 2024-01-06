#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>
#include "lru_cache/hockey_player.h"

template <typename T>
class LRUCache {
    int capacity;
    std::list<int> lruList; // Store keys of cache
    std::unordered_map<int, std::pair<T*, typename std::list<int>::iterator>> cacheMap; // Map id to data and iterator to lruList

public:
    LRUCache(int capacity);
    ~LRUCache();
    T* getPlayer(int id);
    void refer(int id, T* player);
    
    // TODO: Fix this
    bool isEmpty() const {
    return lruList.empty();
    }

    const std::list<int>& getLRUList() const {
        return lruList;
    }
};

#endif // LRU_CACHE_H