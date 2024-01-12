#ifndef NHL_API_H
#define NHL_API_H

#include "lru_cache/hockey_player.h"
#include <vector>
#include <string>

class HockeyData {
public:
    std::vector<HockeyPlayer> getNhlSpotlightPlayers();
    std::vector<HockeyPlayer> getPlayerByName(const std::string& playerName);

private:
    std::string getJsonFromApi(const std::string& url);
    std::vector<HockeyPlayer> parseSpotlightPlayers(const std::string& jsonStr);
    std::vector<HockeyPlayer> parsePlayers(const std::string& jsonStr);
};

#endif // NHL_API_H