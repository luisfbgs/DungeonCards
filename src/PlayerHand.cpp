#include <string>
#include <cstdio>

#include "GameObject.h"
#include "GameData.h"
#include "Component.h"
#include "Common.h"
#include "PlayerHand.h"
#include "Board.h"
#include "Vec2.h"
#include "Vec2Int.h"
#include "InputManager.h"

PlayerHand::PlayerHand(GameObject &associated, int num) 
    : Component(associated), sprite(associated, std::string("assets/img/circle.png")) {
    this->szW = this->szH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
}

void PlayerHand::Update(int dt) {
    (void)dt;

    InputManager &input = InputManager::GetInstance();
    // Mover a carta
    int yMove = input.IsKeyPress('s') - input.IsKeyPress('w');
    int xMove = input.IsKeyPress('d') - input.IsKeyPress('a');
    if(xMove || yMove) {
        ActionHand::Move(this, {xMove, yMove}, this->pos);
    }
}

void PlayerHand::Render() {
    this->sprite.Render();
}

bool PlayerHand::Is(const std::string &type) {
    return type == "PlayerHand";
}

// Coloca o tamanho do sprite pra ser igual o da célula
void PlayerHand::SetScale() {
    Board &board = Board::GetInstance();
    float cellW = board.GetCellW(), cellH = board.GetCellH();

    // Ajusta o tamanho da carta
    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    float scale = std::min(cellW / spriteW, cellH / spriteH);
    this->sprite.SetScale(this->szW * scale, this->szH * scale);

}

int PlayerHand::GetNum() {
    return this->playerNum;
}
