#include <string>
#include <cstdio>

#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "Board.h"
#include "Vec2.h"
#include "Vec2Int.h"

Card::Card(GameObject &associated, std::string file, int hp) : Component(associated),
                                                                sprite(associated, file),
                                                                lifeBar(associated, std::string("assets/img/lifeBar.png")) {
    this->hp = hp;
    this->szW = this->szH = 1;
    this->pos = {0, 0};
}

void Card::Update(int dt) {
    this->lifeBar.SetScale(this->lifeBarSize * this->hp / 100,
                           this->lifeBarSize);
}

void Card::Render() {
    this->sprite.Render();
    this->lifeBar.Render();
}

bool Card::Is(const std::string &type) {
    return type == "Card";
}

// Coloca o tamanho do sprite pra ser igual o da célula
void Card::SetScale() {
    Board &board = Board::GetInstance();
    float cellW = board.GetCellW(), cellH = board.GetCellW();

    // Ajusta o tamanho da carta
    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    float scale = std::min(cellW / spriteW, cellH / spriteH);
    this->sprite.SetScale(this->szW * scale, this->szH * scale);
    
    // Ajusta o tamanho da barra de vida
    spriteW = this->lifeBar.GetWidth();
    spriteH = this->lifeBar.GetHeight();
    this->lifeBarSize = std::min(this->sprite.GetWidthS() / spriteW,
                     this->sprite.GetHeightS() / spriteH);
    this->lifeBar.SetScale(this->lifeBarSize, this->lifeBarSize);
}
