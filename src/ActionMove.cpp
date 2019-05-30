#include "ActionMove.h"
#include "Card.h"
#include "Board.h"

ActionMove::ActionMove(){}

void ActionMove::Run(int idSource, Vec2Int pos, Vec2Int offSet) {
    Card* card = Board::GetInstance().GetCard(idSource).get();
    pos = pos + offSet;
    card->pos = pos/*  + offSet */;
    card->associated.box.lefUp = {
        (float)pos.x * card->sprite.GetWidthS(),
        (float)pos.y * card->sprite.GetHeightS()
    };
}