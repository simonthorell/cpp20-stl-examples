#include "lru_cache/hockey_player.h"

//==============================================================================
// Constructor
//==============================================================================

HockeyPlayer::HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName)
    : id(id), name(name), jersey(jersey), teamName(teamName) {}

//==============================================================================
// Public Methods
//==============================================================================

int HockeyPlayer::getId() const {
    return id;
}

const std::string& HockeyPlayer::getName() const {
    return name;
}

int HockeyPlayer::getJersey() const {
    return jersey;
}

const std::string& HockeyPlayer::getTeamName() const {
    return teamName;
}