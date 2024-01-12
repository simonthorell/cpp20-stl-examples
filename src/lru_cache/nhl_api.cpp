#include "lru_cache/nhl_api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream> // for debugging

using json = nlohmann::json; // for convenience

//=============================================================================
// Method: WriteCallback
// Description: Helper function for getJsonFromApi. This function is called by
//              curl_easy_perform() and is used to write the data from the API
//              into a string.
//=============================================================================
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, 
                            std::string* s) {
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
// Methods: getJsonFromApi, parseSpotlightPlayers, parsePlayers
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
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            // Handle the error, such as a network problem
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                    curl_easy_strerror(res));
        }
    }
    return readBuffer;
}

std::vector<HockeyPlayer> HockeyData::parseSpotlightPlayers(const std::string& jsonStr) {
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

// Needs to dynamically typecheck the JSON data (Suppose due to old data?)
std::vector<HockeyPlayer> HockeyData::parsePlayers(const std::string& jsonStr) {
    auto json = nlohmann::json::parse(jsonStr);
    std::vector<HockeyPlayer> players;

    for (const auto& playerData : json) {
        int id = 0;
        if (!playerData["playerId"].is_null()) {
            id = playerData["playerId"].is_string() ? std::stoi(playerData["playerId"].get<std::string>()) 
                                                    : playerData["playerId"].get<int>();
        }

        std::string name = playerData["name"].is_null() ? "" : playerData["name"].get<std::string>();

        int jerseyNumber = 0;
        if (!playerData["sweaterNumber"].is_null()) {
            jerseyNumber = playerData["sweaterNumber"].is_string() ? std::stoi(playerData["sweaterNumber"].get<std::string>()) 
                                                                   : playerData["sweaterNumber"].get<int>();
        }

        std::string teamName = playerData["lastTeamAbbrev"].is_null() ? "" : playerData["lastTeamAbbrev"].get<std::string>();

        players.emplace_back(id, name, jerseyNumber, teamName);
    }

    return players;
}
//=============================================================================
// Method: getNhlSpotlightPlayers, getPlayerByName
// Description: Retrieves NHL player data from the NHL API.
//=============================================================================
std::vector<HockeyPlayer> HockeyData::getNhlSpotlightPlayers() {
    // https://www.nhl.com/player
    std::string api = "https://api-web.nhle.com/v1/player-spotlight";
    std::string spotlightJsonStr = getJsonFromApi(api);
    return parseSpotlightPlayers(spotlightJsonStr);
    
}

std::vector<HockeyPlayer> HockeyData::getPlayerByName(const std::string& playerName) {
    // Split the playerName into first and last names
    size_t spaceIndex = playerName.find(' ');
    std::string firstName = (spaceIndex != std::string::npos) 
                         ? playerName.substr(0, spaceIndex) : playerName;
    std::string lastName = (spaceIndex != std::string::npos) 
                         ? playerName.substr(spaceIndex + 1) : "";

    // culture = language
    // limit = number of results
    // q = query (player name)
    // active = whether the player is currently active or not

    // Construct the API URL
    std::string api = "https://search.d3.nhle.com/api/v1/search/player?culture=EN&limit=1&q=" 
                      + firstName + "%20" + lastName; // + "&active=false";
    
    // api = "https://search.d3.nhle.com/api/v1/search/player?culture=EN&limit=1&q=Mats%20Sundin&active=false";
    // std::cout << api << std::endl; // for debugging

    // Fetch the JSON string from the API
    std::string playersJsonStr = getJsonFromApi(api);

    // Parse the players from the JSON string
    return parsePlayers(playersJsonStr);
}

// Use example:
// HockeyData hd;
//     try {
//         std::vector<HockeyPlayer> players = hd.getPlayerByName("Mats Sundin");

//         for (const auto& player : players) {
//             std::cout << "ID: " << player.id
//                     << ", Name: " << player.name
//                     << ", Jersey: " << player.jersey
//                     << ", Team: " << player.teamName << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
