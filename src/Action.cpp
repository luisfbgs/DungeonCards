#include "Action.h"
#include "Board.h"

void Action::Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet) {
    pos += offSet;
    Board &board = Board::GetInstance();
    pos.x = std::min(pos.x, board.GetColumns() - 1);
    pos.y = std::min(pos.y, board.GetRows() - 1);
    pos.x = std::max(pos.x, 0);
    pos.y = std::max(pos.y, 0);
    sourcePtr->associated.box.lefUp = {
        (float)pos.x * board.GetCellW(),
        (float)pos.y * board.GetCellH()
    };
    sourcePtr->associated.box.lefUp += {
        (board.GetCellW() - sourcePtr->sprite.GetWidthS()) / 2,
        (board.GetCellH() - sourcePtr->sprite.GetHeightS()) / 2
        };
    
    sourcePtr->pos = pos;
}

void Action::Attack(Card* sourcePtr, int damage) {
    sourcePtr->hp -= damage;
}