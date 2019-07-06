#pragma once

#include <string>
#include <memory>

#include "GameObject.h"
#include "Sprite.h"

enum Turn{
    PlayerAttack,
    EnemyAttack,
    _Event,
    PlayerSkill
};

const static int TURN = 4;
const std::string turnName[TURN] = {
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
    ~TurnState();

private:
    TurnState();
    std::shared_ptr<Sprite> turnSprite;
    std::shared_ptr<GameObject> turnSpriteGO;
    static TurnState *instance;
    void SetScale();
};