#include "lru_cache/hockey_player.h"

//==============================================================================
// Constructor
//==============================================================================
HockeyPlayer::HockeyPlayer(int id, const std::string& name, int jersey, const std::string& teamName)
    : id(id), name(name), jersey(jersey), teamName(teamName) {}