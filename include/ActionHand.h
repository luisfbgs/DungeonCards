#pragma once

#include "PlayerHand.h"

class PlayerHand;

class ActionHand {
public:
    static bool Move(PlayerHand* sourcePtr, Vec2Int pos, Vec2Int offSet = {0, 0});
};

