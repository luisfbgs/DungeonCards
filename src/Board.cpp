#include <vector>
#include <memory>
#include <cstdio>

#include "Game.h"
#include "Card.h"
#include "Board.h"
#include "Vec2Int.h"

void Board::Init(int rows, int columns, float sizeW, float sizeH) {
    this->rows = rows;
    this->columns = columns;
    this->cellH = sizeH / rows;
    this->cellW = sizeW / columns;
}

int Board::AddCard(std::shared_ptr<Card> card) {
    this->cards[card->GetNum()] = card;
    card->SetScale();
    return cards.size();
}

Vec2Int Board::GetBoardPos(int id) {
    return cards[id]->pos;
}

std::shared_ptr<Card> Board::GetCard(int id) {
    return this->cards[id];
}

Board& Board::GetInstance() {
    static Board instance;
    return instance;
}

float Board::GetCellW() {
    return this->cellW;
}

float Board::GetCellH(){
    return this->cellH;
}

int Board::GetRows() {
    return this->rows;
}

int Board::GetColumns(){
    return this->columns;
}

void Board::Reset() {
    cards.clear();
}