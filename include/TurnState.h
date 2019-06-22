#pragma once

#include <string>

enum Turn{
    PlayerAttack,
    EnemyAttack,
    Event,
    PlayerSkill
};

const std::string turnName[4] = {
    "PlayerAttack",
    "EnemyAttack",
    "Event",
    "PlayerSkill"
};

class TurnState {
public:
    static Turn current;
    static void Init();
    static void Next();
};