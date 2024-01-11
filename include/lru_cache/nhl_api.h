#ifndef NHL_API_H
#define NHL_API_H

#include "lru_cache/hockey_player.h"
#include <vector>
#include <string>

class HockeyData {
public:
    std::vector<HockeyPlayer> getAllPlayers();

private:
    std::string getJsonFromApi(const std::string& url);
    std::vector<HockeyPlayer> parsePlayers(const std::string& jsonStr);
};

#endif // NHL_API_H