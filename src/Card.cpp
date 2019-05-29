#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "Vec2.h"

Card::Card(GameObject &associated, std::string file, int hp) : Component(associated), sprite(associated, file) {
    this->hp = hp;
    this->szW = this->szH = 1;
    this->posX = this->posY = 0;
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
    this->sprite.SetScale(this->szW * cellW / spriteW, this->szH * cellH / spriteH);
}

void Card::Move(int posX, int posY) {
    this->posX = posY;
    this->posY = posY;
    this->associated.box.lefUp = {posX * this->sprite.GetWidthS(), posY * this->sprite.GetHeightS()};
}