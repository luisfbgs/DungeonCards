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

PlayerHand::PlayerHand(std::shared_ptr<GameObject> associated, std::string file, int num, int playerDamage) 
    : Component(associated), sprite(associated, file) {
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 1};
    this->playerNum = num;
    this->SetScale();
    this->myCard = Board::GetInstance().GetCard(this->playerNum).get();
    this->playerDamage = playerDamage;
    ActionHand::Move(this, {0, -1}, this->pos);
}

void PlayerHand::Update(int dt) {
    (void)dt;
    if(!Board::GetInstance().GetCard(this->playerNum).get()) {
        this->associated->RequestDelete();
        return;
    }
    if(TurnState::turnEnded || this->myCard->isDead) {
        return;
    }
    switch (TurnState::current) {
        case PlayerAttack:
            this->MoveOnBoard(); 
            this->Attack();
            Event::occured = false;
            break;
        case PlayerSkill: {
            this->MoveOnBoard(); 
            if (!this->myCard->acted){
                // gambiarra: player 1 dano em dobro, e o outro heala a si mesmo
                if (this->playerNum == 1) {
                    if(!this->lastTarget.expired() && !this->lastTarget.lock()->isDead) {
                        CardSkill::DoubleDamage(this->lastTarget.lock().get(), this->myCard);
                    }
                    this->myCard->acted = true;
                    this->myCard->lastActed = TurnState::current;
                } 
                else if (this->playerNum == 2) {
                    this->Heal();
                }
            }
            break;
        }
        case Event: {
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
        if(!this->lastTarget.expired() && !this->lastTarget.lock()->isDead) {
            Action::Attack(this->myCard, this->playerDamage, this->lastTarget.lock()->GetNum());
        }
    }
}

void PlayerHand::Heal(){
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Cura a posição atual
    if(input.IsKeyPress(bAttack[cId])) {
        this->lastTarget = Board::GetInstance().GetCard(this->pos);
        if(!this->lastTarget.expired() && !this->lastTarget.lock()->isDead) {
            CardSkill::HealCard(this->lastTarget.lock().get());
            this->myCard->acted = true;
            this->myCard->lastActed = TurnState::current;
        }
    }
}

void PlayerHand::Render() {
    if(TurnState::current == PlayerAttack || TurnState::current == PlayerSkill) {
        if(!this->myCard->acted && !TurnState::turnEnded && !this->myCard->isDead) {
            this->sprite.Render();
        }
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
