#ifndef HOCKEY_PLAYER_H
#define HOCKEY_PLAYER_H

#include <string>

class HockeyPlayer {
public:
    int id;
    std::string name;
    int jersey;
    std::string teamName;
    
    // Default constructor (TODO/Understand: Why do we need this?)
    HockeyPlayer() : id(0), jersey(0) {}  // Default constructor

    // Custom constructor
    HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName);

    // // Custom constructor 2
    // HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName)
    //     : id(id), name(name), jersey(jersey), teamName(teamName) {}
};

#endif // HOCKEY_PLAYER_H