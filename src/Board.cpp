#include <vector>
#include <memory>
#include "Game.h"
#include "Card.h"
#include "Board.h"
#include "Vec2Int.h"

void Board::Init(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    this->cellH = Game::GetInstance().GetHeight() / rows;
    this->cellW = Game::GetInstance().GetWidth() / columns;
}

int Board::AddCard(std::shared_ptr<Card> card) {
    this->cards.emplace_back(card);
    card->SetScale(this->cellW, this->cellH);
    return int(cards.size() - 1);
}

void Board::MoveCard(int id, Vec2Int pos, Vec2Int offset){
    cards[id]->Move(pos + offset);
}

Vec2Int Board::GetBoardPos(int id) {
    return cards[id]->pos;
}