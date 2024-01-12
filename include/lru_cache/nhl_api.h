#ifndef NHL_API_H
#define NHL_API_H

#include "lru_cache/hockey_player.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>

struct GameInfo {
    std::string startTimeUTC;
    std::string homeTeam;
    std::string awayTeam;

    std::string getFormattedTime() const {
        std::tm tm = {};
        std::stringstream ss(startTimeUTC);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        if (ss.fail()) {
            return "Invalid Time";
        }
        std::time_t time = std::mktime(&tm);
        std::stringstream formatted;
        formatted << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M");
        return formatted.str();
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::left
            << "Game Time: " << std::setw(20) << getFormattedTime()
            << homeTeam  << "  -  " << awayTeam;
        return oss.str();
    }
};

class HockeyData {
public:
    std::vector<HockeyPlayer> getNhlSpotlightPlayers();
    std::vector<HockeyPlayer> getPlayerByName(const std::string& playerName, int searchLimit);
    // Additional cool features:
    std::vector<GameInfo> getUpcomingGames();

private:
    std::string getJsonFromApi(const std::string& url);
    std::vector<HockeyPlayer> parseSpotlightPlayers(const std::string& jsonStr);
    std::vector<HockeyPlayer> parsePlayers(const std::string& jsonStr);
};

#endif // NHL_API_H