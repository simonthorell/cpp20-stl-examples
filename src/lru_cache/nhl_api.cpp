#include "lru_cache/nhl_api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // for convenience

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
    for (const auto& team : json["teams"]) {
        std::string teamName = team["name"];
        for (const auto& playerData : team["roster"]["roster"]) {
            int id = playerData["person"]["id"];
            std::string name = playerData["person"]["fullName"];
            int jerseyNumber = playerData.value("jerseyNumber", 0);
            players.emplace_back(id, name, jerseyNumber, teamName);
        }
    }
    return players;
}

std::vector<HockeyPlayer> HockeyData::getAllPlayers() {
    std::string teamsJsonStr = getJsonFromApi("https://statsapi.web.nhl.com/api/v1/teams?expand=team.roster");
    return parsePlayers(teamsJsonStr);
}