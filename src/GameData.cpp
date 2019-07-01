#include <vector>
#include <memory>

#include "GameData.h"
#include "Player.h"

bool GameData::playerVictory = false;
bool GameData::quitAll = false;
bool GameData::restart = false;
int GameData::playersCount = 0;
int GameData::enemyCount = 0;
int GameData::stagesBeated = 0;
int GameData::runningAnimations = 0;
std::vector<std::weak_ptr<Player>> GameData::players;