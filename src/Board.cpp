#include <vector>
#include <memory>
#include <map>
#include <string>
#include <cstdio>

#include "Game.h"
#include "Card.h"
#include "Board.h"
#include "Vec2Int.h"
#include "Action.h"
#include "ActionMove.h"

// Board::ActionMap.insert ( std::pair<std::string,std::shared_ptr<ActionMove>("Move", std::shared_ptr<ActionMove>()) );

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
    printf("[Board::MoveCard] %p\n", this->cards[id].get());
    this->cards[id]->Move(pos + offset);
}

Vec2Int Board::GetBoardPos(int id) {
    return cards[id]->pos;
}

std::shared_ptr<Card> Board::GetCard(int id) {
    auto card = this->cards[id];
    printf("[Board::GetCard] %p\n", card.get());
    return card;
}
Board& Board::GetInstance() {
    static Board instance;
    return instance;
}

Action* Board::GetAction(ActionNames id) {
    return ActionMap[id];
}

void Board::InitActionMap() {
    ActionMap.insert( std::pair<ActionNames, Action*>(ActionNames::MOVE, new ActionMove()));
}