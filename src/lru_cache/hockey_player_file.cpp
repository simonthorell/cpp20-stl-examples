#include "lru_cache/hockey_player_file.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

//==============================================================================
// Constructor & Destructor
//==============================================================================

HockeyPlayerFile::HockeyPlayerFile(const std::string& fileName) : fileName(fileName) {
    file.open(fileName, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening the file for reading and writing." << std::endl;
        return;
    }

    readPlayersFromFile();
}

HockeyPlayerFile::~HockeyPlayerFile() {
    writePlayersToFile();
    file.close();
}

//==============================================================================
// Public Methods
//==============================================================================

void HockeyPlayerFile::generateRandomPlayers(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < count; ++i) {
        HockeyPlayer player;
        player.id = players.size() + 1;
        player.name = "Player" + std::to_string(player.id);
        player.jersey = std::uniform_int_distribution<int>(1, 99)(gen);
        player.teamName = "Team" + std::to_string(std::uniform_int_distribution<int>(1, 30)(gen));

        players.push_back(player);
    }
}

void HockeyPlayerFile::addPlayer(const HockeyPlayer& player) {
    players.push_back(player);
}

void HockeyPlayerFile::deletePlayer(int id) {
    auto it = std::remove_if(players.begin(), players.end(), [id](const HockeyPlayer& p) {
        return p.id == id;
    });

    if (it != players.end()) {
        players.erase(it, players.end());
    }
}

void HockeyPlayerFile::displayPlayers() {
    for (const auto& player : players) {
        std::cout << "ID: " << player.id << ", Name: " << player.name
                  << ", Jersey: " << player.jersey << ", Team: " << player.teamName << std::endl;
    }
}

//==============================================================================
// Private Methods
//==============================================================================

void HockeyPlayerFile::readPlayersFromFile() {
    if (!file.is_open()) {
        return;
    }

    file.seekg(0, std::ios::beg);
    players.clear();

    while (!file.eof()) {
        HockeyPlayer player;
        file >> player.id >> player.name >> player.jersey >> player.teamName;
        players.push_back(player);
    }

    // Remove the last empty player entry
    if (!players.empty()) {
        players.pop_back();
    }
}

void HockeyPlayerFile::writePlayersToFile() {
    if (!file.is_open()) {
        return;
    }

    file.close();
    file.open(fileName, std::ios::out | std::ios::trunc);

    for (const auto& player : players) {
        file << player.id << " " << player.name << " " << player.jersey << " " << player.teamName << "\n";
    }
}