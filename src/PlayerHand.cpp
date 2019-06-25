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
#include "Control.h"
#include "TurnState.h"

PlayerHand::PlayerHand(GameObject &associated, int num, std::string file) 
    : Component(associated), sprite(associated, file) {
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->SetScale();

    this->associated.box.leftUp = {
        Board::GetInstance().GetOffset().y,
        Board::GetInstance().GetOffset().x
    };
}

void PlayerHand::Update(int dt) {
    (void)dt;
    Card *myCard = Board::GetInstance().GetCard(this->playerNum).get();
    if(!myCard) {
        this->associated.RequestDelete();
        return;
    }
    switch (TurnState::current) {
        case PlayerAttack:
            this->MoveOnBoard(); 
            this->Attack(myCard); 
            break;
        
        default:
            break;
    }
}

void PlayerHand::MoveOnBoard() {
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Mover a mão
    int yMove = input.IsKeyPress(bDown[cId]) - input.IsKeyPress(bUp[cId]);
    int xMove = input.IsKeyPress(bRight[cId]) - input.IsKeyPress(bLeft[cId]);
    if(xMove || yMove) {
        ActionHand::Move(this, {xMove, yMove}, this->pos);
    }
}

void PlayerHand::Attack(Card* myCard){
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Ataca a posição atual
    if(input.IsKeyPress(bAttack[cId])) {
        auto target = Board::GetInstance().GetCard(this->pos);
        if(target) {
            Action::Attack(myCard, 3, target->GetNum());
        }
    }
}

void PlayerHand::Render() {
    if(TurnState::current == PlayerAttack || TurnState::current == PlayerSkill) {
        this->sprite.Render();
    }
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
