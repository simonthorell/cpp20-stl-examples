#ifndef HOCKEY_PLAYER_H
#define HOCKEY_PLAYER_H

#include <string>

class HockeyPlayer {
public:
    int id;
    std::string name;
    int jersey;
    std::string teamName;
    
    // Default constructor
    HockeyPlayer() : id(0), jersey(0) {}  // Default constructor

    // Custom constructor
    HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName);
};

#endif // HOCKEY_PLAYER_H