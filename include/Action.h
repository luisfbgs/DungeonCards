#ifndef ACTION_NAMESPACE
#define ACTION_NAMESPACE
#include "Card.h"

class Card;
enum ActionId {
    MOVE
};
class Action {
    // static std::map <Action, *> ActionMap; // Fazer map Action -> funcao correspondente
public:
    static void Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet = {0, 0});
};

#endif