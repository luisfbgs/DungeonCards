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
    "PlayerAttack",
    "EnemyAttack",
    "Event",
    "PlayerSkill"
};

class TurnState {
public:
    static const float PROPORCAO;
    static Turn current;
    static void Init();
    static void Next();
    static void Render();
private:
    TurnState();
    Sprite turnSprite;
    GameObject turnSpriteGO;
    static TurnState *instance;
    void SetScale();
};