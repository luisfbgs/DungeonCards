#pragma once

#include <string>

#include "GameObject.h"
#include "Sprite.h"

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
private:
    TurnState();
    Sprite turnSprite;
    GameObject turnSpriteGO;
    static TurnState *instance;
    void SetScale();
public:
    static Turn current;
    static void Init();
    static void Next();
    static void Render();
};