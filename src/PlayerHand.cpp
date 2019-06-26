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
#include "CardSkill.h"
#include "Event.h"

PlayerHand::PlayerHand(GameObject &associated, int num, std::string file) 
    : Component(associated), sprite(associated, file) {
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->SetScale();
    this->myCard = Board::GetInstance().GetCard(this->playerNum).get();

    this->associated.box.leftUp = {
        Board::GetInstance().GetOffset().y,
        Board::GetInstance().GetOffset().x
    };
}

void PlayerHand::Update(int dt) {
    (void)dt;
    if(!this->myCard) {
        this->associated.RequestDelete();
        return;
    }
    switch (TurnState::current) {
        case PlayerAttack:
            this->MoveOnBoard(); 
            this->Attack();
            Event::occured = false;
            break;
        case PlayerSkill: {
            if (!this->myCard->acted){
                // gambiarra: player 1 dano em dobro, e o outro heala a si mesmo
                if (this->playerNum == 1) {
                    if(this->lastTarget) {
                        CardSkill::DoubleDamage(this->lastTarget.get(), this->myCard);
                    }
                    this->myCard->acted = true;
                    this->myCard->lastActed = TurnState::current;
                } 
                else if (this->playerNum == 2) {
                    CardSkill::HealCard(this->myCard);
                    this->myCard->acted = true;
                    this->myCard->lastActed = TurnState::current;
                }
            }
            break;
        }
        case _Event: {
            if(not Event::occured) {
                Event::Run();
                Event::occured = true;
            }
            break;
        }
        default:{
            break;
        }
    }
}

void PlayerHand::MoveOnBoard() {
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Mover a mão
    int yMove = input.IsKeyPress(buttonDown[cId]) - input.IsKeyPress(buttonUp[cId]);
    int xMove = input.IsKeyPress(buttonRight[cId]) - input.IsKeyPress(buttonLeft[cId]);
    if(xMove || yMove) {
        ActionHand::Move(this, {xMove, yMove}, this->pos);
    }
}

void PlayerHand::Attack(){
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Ataca a posição atual
    if(input.IsKeyPress(bAttack[cId])) {
        this->lastTarget = Board::GetInstance().GetCard(this->pos);
        if(this->lastTarget) {
            Action::Attack(this->myCard, 3, this->lastTarget->GetNum());
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
