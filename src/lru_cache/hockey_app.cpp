#include "lru_cache/hockey_app.h"
#include <fstream>
#include <random>
#include <iostream>

HockeyApp::HockeyApp(int cacheSize, const std::string& filename)
    : cache(new LRUCache<HockeyPlayer>(cacheSize)), filename(filename) {}

HockeyApp::~HockeyApp() {
    delete cache;
}

void HockeyApp::generateRandomPlayers() {
    std::ofstream file(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 99);
    for (int i = 0; i < 100000; ++i) {
        file << i << ",Player" << i << "," << dis(gen) << ",Team" << dis(gen) << std::endl;
    }
}

void HockeyApp::run() {
    generateRandomPlayers();

    // Example usage: Fetch player with ID 5
    HockeyPlayer* player = cache->getPlayer(5);
    if (player) {
        std::cout << "Player found: " << player->name << std::endl;
    } else {
        std::cout << "Player not found in cache. Reading from file and adding to cache." << std::endl;
        // Implement reading from file and adding to cache logic here
    }
}
