#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Card.h"

namespace GameData {
    extern bool playerVictory;
    extern bool quitAll;
    extern bool restart; 
    extern int playersCount; 
    extern int enemyCount; 
    extern int stagesBeated;
    extern int runningAnimations;
    extern std::vector<std::weak_ptr<Player>> players;
    extern std::vector<std::weak_ptr<Card>> enemies;
    extern void AddAliveEnemies(std::vector<Card*> &targets);
    extern void AddAlivePlayers(std::vector<Card*> &targets);
};
