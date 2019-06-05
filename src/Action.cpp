#include "Action.h"
#include "Board.h"

bool Action::Move(Card* sourcePtr, Vec2Int pos, Vec2Int offSet) {
    pos += offSet;
    Board &board = Board::GetInstance();
    pos.x = std::min(pos.x, board.GetColumns() - 1);
    pos.y = std::min(pos.y, board.GetRows() - 1);
    pos.x = std::max(pos.x, 0);
    pos.y = std::max(pos.y, 0);
    if(sourcePtr->pos != pos) {
        sourcePtr->associated.box.leftUp = {
            (float)pos.x * board.GetCellW(),
            (float)pos.y * board.GetCellH()
        };
        sourcePtr->associated.box.leftUp += {
            (board.GetCellW() - sourcePtr->sprite.GetWidthS()) / 2,
            (board.GetCellH() - sourcePtr->sprite.GetHeightS()) / 2
            };
        sourcePtr->pos = pos;
        return true;
    }
    return false;
}

bool Action::Attack(Card* sourcePtr, int damage, int targetId) {
    Board &board = Board::GetInstance();
    if(board.GetCard(targetId) != nullptr) {
        board.GetCard(targetId)->hp -= damage;
        return true;
    }
    return false;
}