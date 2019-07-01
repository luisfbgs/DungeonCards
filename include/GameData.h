#pragma once

#include <vector>
#include <memory>

#include "Player.h"

namespace GameData {
    extern bool playerVictory;
    extern bool quitAll;
    extern bool restart; 
    extern int playersCount; 
    extern int enemyCount; 
    extern int stagesBeated;
    extern int runningAnimations;
    extern std::vector<std::weak_ptr<Player>> players;
};
