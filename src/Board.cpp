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

std::map <ActionNames, Action*> Board::ActionMap;

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
    this->cards[id]->Move(pos + offset);
}

Vec2Int Board::GetBoardPos(int id) {
    return cards[id]->pos;
}

std::shared_ptr<Card> Board::GetCard(int id) {
    auto card = this->cards[id];
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