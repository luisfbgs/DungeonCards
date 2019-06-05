#pragma once

#include "Card.h"

class Card;
enum ActionId {
    MOVE,
    ATTACK
};
class Action {
    // static std::map <Action, *> ActionMap; // Fazer map Action -> funcao correspondente
public:
    static bool Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet = {0, 0});
    static bool Attack(Card* sourcePtr, int damage, int targetId);
};

