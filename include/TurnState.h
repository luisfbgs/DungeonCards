#pragma once

#include <string>

#include "GameObject.h"
#include "Sprite.h"

enum Turn{
    PlayerAttack,
    EnemyAttack,
    _Event,
    PlayerSkill
};

const std::string turnName[4] = {
    "playerAttack",
    "enemyAttack",
    "event",
    "playerSkill"
};

class TurnState {
public:
    static Turn current;
    static void Init();
    static void Next();
    static void Render();
    static bool turnEnded;

private:
    TurnState();
    Sprite turnSprite;
    GameObject turnSpriteGO;
    static TurnState *instance;
    void SetScale();
};