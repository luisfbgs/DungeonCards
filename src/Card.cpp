#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "Vec2.h"
#include "Vec2Int.h"

Card::Card(GameObject &associated, std::string file, int hp) : Component(associated), sprite(associated, file) {
    this->hp = hp;
    this->szW = this->szH = 1;
    this->pos = {0, 0};
}

void Card::Update(int dt) {}

void Card::Render() {
    this->sprite.Render();
}

bool Card::Is(const std::string &type) {
    return type == "Card";
}

void Card::SetScale(float cellW, float cellH) {
    // Coloca o tamanho do sprite pra ser igual o da célula
    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    float scale = std::min(cellW / spriteW, cellH / spriteH);
    this->sprite.SetScale(this->szW * scale, this->szH);
}

void Card::Move(Vec2Int pos) {
    this->pos = pos;
    this->associated.box.lefUp = {(float)pos.x * this->sprite.GetWidthS(), (float)pos.y * this->sprite.GetHeightS()};
}