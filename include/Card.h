#pragma once

#include <string>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2Int.h"
#include "Action.h"
#include "TurnState.h"

class Board;
class Action;

class Card : public Component {
friend Board;
friend Action;
public:
    Card(GameObject &associated, std::string file, int num = 0, int hp = 9);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void SetScale();
    int GetNum();
    Vec2Int GetPos();
private:
    // playerNum é positivo para jogadores e negativo para inimigos
    int playerNum;
    int hp;
    Turn lastActed;
    bool acted;
    int sizeW, sizeH;
    Vec2Int pos;
    Sprite sprite;
    Sprite lifeBar;
};