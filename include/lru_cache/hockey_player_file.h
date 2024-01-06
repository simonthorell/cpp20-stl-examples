#ifndef HOCKEY_PLAYER_FILE_H
#define HOCKEY_PLAYER_FILE_H

#include <string>
#include <vector>
#include <fstream>

struct HockeyPlayer {
    int id;
    std::string name;
    int jersey;
    std::string teamName;
};

class HockeyPlayerFile {
public:
    HockeyPlayerFile(const std::string& fileName);
    ~HockeyPlayerFile();

    void generateRandomPlayers(int count);
    void addPlayer(const HockeyPlayer& player);
    void deletePlayer(int id);
    void displayPlayers();

private:
    std::string fileName;
    std::fstream file;
    std::vector<HockeyPlayer> players;

    void readPlayersFromFile();
    void writePlayersToFile();
};

#endif // HOCKEY_PLAYER_FILE_H