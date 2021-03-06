#include "ActionHand.h"
#include "PlayerHand.h"
#include "Board.h"

bool ActionHand::Move(PlayerHand* sourcePtr, Vec2Int pos, Vec2Int offSet) {
    pos += offSet;
    Board &board = Board::GetInstance();
    pos.x = std::min(pos.x, board.GetColumns() - 1);
    pos.y = std::min(pos.y, board.GetRows() - 1);
    pos.x = std::max(pos.x, 0);
    pos.y = std::max(pos.y, 0);
    if(sourcePtr->pos != pos) {
        sourcePtr->associated->box.leftUp = {
            (float)pos.x * board.GetCellW(),
            (float)pos.y * board.GetCellH()
        };
        sourcePtr->associated->box.leftUp += {
            board.GetOffset().x,
            board.GetOffset().y
        };
        sourcePtr->associated->box.leftUp += {
            (board.GetCellW() - sourcePtr->sprite.GetWidthS()) / 2,
            (board.GetCellH() - sourcePtr->sprite.GetHeightS()) / 2
        };
        sourcePtr->pos = pos;
        return true;
    }
    return false;
}
