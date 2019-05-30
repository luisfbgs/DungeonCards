#include "Action.h"
#include "Board.h"

void Action::Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet) {
    pos += offSet;
    Board &board = Board::GetInstance();
    sourcePtr->associated.box.lefUp = {
        (float)pos.x * board.GetCellW(),
        (float)pos.y * board.GetCellH()
    };
    sourcePtr->pos = pos;
}