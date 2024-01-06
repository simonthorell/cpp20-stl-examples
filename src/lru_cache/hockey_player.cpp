#include "lru_cache/hockey_player.h"

//==============================================================================
// Constructor: HockeyPlayer
// Parameters: id - id of player
//             name - name of player
//             jersey - jersey number of player
//             teamName - name of team player is on
// Description: Constructor for HockeyPlayer.
//==============================================================================
HockeyPlayer::HockeyPlayer(int id, const std::string& name, 
                           int jersey, const std::string& teamName)
    : id(id), name(name), jersey(jersey), teamName(teamName) {}