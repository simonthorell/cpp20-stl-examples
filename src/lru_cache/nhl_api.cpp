#include "lru_cache/nhl_api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // for convenience

//=============================================================================
// Method: WriteCallback
// Description: Helper function for getJsonFromApi. This function is called by
//              curl_easy_perform() and is used to write the data from the API
//              into a string.
//=============================================================================
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
        return newLength;
    }
    catch(std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
}
//=============================================================================
// Methods: getJsonFromApi, parsePlayers
// Description: Retrieves JSON data from the specified API. The JSON data is
//              then parsed and converted into a vector of HockeyPlayer objects.
//=============================================================================
std::string HockeyData::getJsonFromApi(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // Some APIs require a user-agent
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            // Handle the error, such as a network problem
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    }
    return readBuffer;
}

std::vector<HockeyPlayer> HockeyData::parsePlayers(const std::string& jsonStr) {
    auto json = nlohmann::json::parse(jsonStr);
    std::vector<HockeyPlayer> players;
    for (const auto& playerData : json) {
        int id = playerData.value("playerId", 0);
        std::string name = playerData["name"].value("default", "");
        int jerseyNumber = playerData.value("sweaterNumber", 0);
        std::string teamName = playerData.value("teamTriCode", "");
        
        players.emplace_back(id, name, jerseyNumber, teamName);
    }
    return players;
}
//=============================================================================
// Method: getNhlSpotlightPlayers, getAllPlayers
// Description: Retrieves NHL player data from the NHL API.
//=============================================================================
std::vector<HockeyPlayer> HockeyData::getNhlSpotlightPlayers() {
    std::string api = "https://api-web.nhle.com/v1/player-spotlight";
    std::string spotlightJsonStr = getJsonFromApi(api);
    return parsePlayers(spotlightJsonStr);
    
}

std::vector<HockeyPlayer> HockeyData::getAllPlayers() {
    std::string teamsJsonStr = getJsonFromApi("https://statsapi.web.nhl.com/api/v1/teams?expand=team.roster");
    return parsePlayers(teamsJsonStr);
}