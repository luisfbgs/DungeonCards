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
#include "Action.h"
#include "InputManager.h"
;
PlayerHand::PlayerHand(GameObject &associated, int num, std::string file,
    char leftMove, char rightMove, char upMove, char downMove) 
    : Component(associated), sprite(associated, file) {
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->SetScale();
    this->leftMove = leftMove;  this->rightMove = rightMove;
    this->upMove = upMove;  this->downMove = downMove;
}

void PlayerHand::Update(int dt) {
    printf("me! ===> %d\n", this->playerNum);
    (void)dt;
    Card *myCard = Board::GetInstance().GetCard(this->playerNum).get();
    if(!myCard) {
        this->associated.RequestDelete();
        return;
    }
    InputManager &input = InputManager::GetInstance();
    // Mover a mão
    int yMove = input.IsKeyPress(this->downMove) - input.IsKeyPress(upMove);
    int xMove = input.IsKeyPress(this->rightMove) - input.IsKeyPress(this->leftMove);
    if(xMove || yMove) {
        ActionHand::Move(this, {xMove, yMove}, this->pos);
    }

    // Ataca a posição atual
    if(input.IsKeyPress('k')) {
        auto target = Board::GetInstance().GetCard(this->pos);
        if(target) {
            Action::Attack(myCard, 3, target->GetNum());
        }
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
    this->sprite.SetScale(this->sizeW * scale, this->sizeH * scale);

}

int PlayerHand::GetNum() {
    return this->playerNum;
}