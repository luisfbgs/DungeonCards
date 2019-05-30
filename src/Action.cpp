#include "Action.h"

void Action::Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet) {
    pos = pos + offSet;
    sourcePtr->pos = pos/*  + offSet */;
    sourcePtr->associated.box.lefUp = {
        (float)pos.x * sourcePtr->sprite.GetWidthS(),
        (float)pos.y * sourcePtr->sprite.GetHeightS()
    };
}