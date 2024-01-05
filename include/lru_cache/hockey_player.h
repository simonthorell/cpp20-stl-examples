#ifndef HOCKEY_PLAYER_H
#define HOCKEY_PLAYER_H

#include <string>

class HockeyPlayer {
public:
    HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName);
    
    int getId() const;
    const std::string& getName() const;
    int getJersey() const;
    const std::string& getTeamName() const;

private:
    int id;
    std::string name;
    int jersey;
    std::string teamName;
};

#endif // HOCKEY_PLAYER_H