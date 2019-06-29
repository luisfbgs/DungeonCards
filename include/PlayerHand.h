#pragma once

#include <string>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2Int.h"
#include "ActionHand.h"
#include "Card.h"
#include <memory>

class Board;
class ActionHand;

class PlayerHand : public Component {
friend Board;
friend ActionHand;
public:
    PlayerHand(GameObject &associated, int num, std::string file);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void SetScale();
    int GetNum();
private:
    void Attack();
    void Heal();
    Card *myCard;
    void MoveOnBoard();
    // playerNum é positivo para jogadores e negativo para inimigos
    int playerNum;
    int sizeW, sizeH;
    Vec2Int pos;
    Sprite sprite;
    std::weak_ptr<Card> lastTarget;
    bool actedSkill;
};