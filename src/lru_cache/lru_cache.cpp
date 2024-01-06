#include "lru_cache/lru_cache.h"

template <typename T>
LRUCache<T>::LRUCache(int capacity) : capacity(capacity) {}

template <typename T>
LRUCache<T>::~LRUCache() {
    for (auto &pair : cacheMap) {
        delete pair.second.first;
    }
}

template <typename T>
T* LRUCache<T>::getPlayer(int id) {
    if (cacheMap.find(id) == cacheMap.end())
        return nullptr;
    refer(id, cacheMap[id].first);
    return cacheMap[id].first;
}

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

// Explicit template instantiation
template class LRUCache<HockeyPlayer>;