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
    if(this->GetCard(id) != nullptr)
        return this->GetCard(id)->pos;
    return {0, 0};
}

std::shared_ptr<Card> Board::GetCard(int id) {
    if(this->cards.count(id)) {
        if(!this->cards[id].expired()) {
            return this->cards[id].lock();
        }
        this->cards.erase(id);
    }
    return nullptr;
}

std::shared_ptr<Card> Board::GetCard(int x, int y) {
    Vec2Int pos = {x, y};
    auto card = this->cards.begin();
    while(card != this->cards.end()) {
        if(card->second.expired()) {
            card = this->cards.erase(card);
        }
        else {
            if(card->second.lock()->GetPos() == pos) {
                return card->second.lock();
            }
            card++;
        }
    }
    return nullptr;
}

std::shared_ptr<Card> Board::GetCard(Vec2Int vec) {
    return this->GetCard(vec.x, vec.y);
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