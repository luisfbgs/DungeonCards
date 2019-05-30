#include "ActionMove.h"
#include "Card.h"
#include "Board.h"

ActionMove::ActionMove(){}

void ActionMove::Run(int idSource, Vec2Int pos, Vec2Int offSet) {
    Card* card = Board::GetInstance().GetCard(idSource).get();
    card->Move(pos  + offSet);
}