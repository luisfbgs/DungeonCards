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
    this->onSkill = false;
    this->selectedSkill = -1;
    this->skillPos = 0;
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
            this->selectedSkill = -1;
            break;
        case PlayerSkill: {
            if (!this->myCard->acted){
                if(this->selectedSkill == -1) {
                    this->MoveOnSkill();
                }
                else {
                    if(CardSkill::IsPassive(this->selectedSkill)) {
                        this->myCard->acted = CardSkill::Run(this->selectedSkill, this->pos, this->myCard, this->lastTarget);
                        if(!this->myCard->acted) {
                            this->selectedSkill = -1;
                        }
                    }
                    else {
                        this->MoveOnBoard();
                        this->myCard->acted = this->CastSkill();
                    }
                }
                if(this->myCard->acted) {
                    this->myCard->lastActed = TurnState::current;
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
    // Coloca a mao na posicao que estava antes do turno de skill
    if (this->onSkill) {
        ActionHand::Move(this, {1, 0}, this->pos);
        ActionHand::Move(this, {-1, 0}, this->pos);
        ActionHand::Move(this, {1, 0}, this->pos);
        ActionHand::Move(this, {-1, 0}, this->pos);
        this->onSkill = false;
    }
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Mover a mão
    int yMove = input.IsKeyPress(buttonDown[cId]) - input.IsKeyPress(buttonUp[cId]);
    int xMove = input.IsKeyPress(buttonRight[cId]) - input.IsKeyPress(buttonLeft[cId]);
    if(xMove || yMove) {
        ActionHand::Move(this, {xMove, yMove}, this->pos);
        printf("MoveuBoard %f %f\n", this->associated->box.leftUp.x, this->associated->box.leftUp.y);
    
    }
}

void PlayerHand::Attack(){
    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    // Ataca a posição atual
    if(input.IsKeyPress(buttonAttack[cId])) {
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
    if(input.IsKeyPress(buttonAttack[cId])) {
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

void PlayerHand::MoveOnSkill() {
    // Coloca a mao na posicao que de uma skill
    if (!this->onSkill) {
        Vec2 pos = this->myCard->associated->box.leftUp;
        pos.y += 0.35f * this->myCard->associated->box.h;
        pos.x -= 0.5f * this->myCard->associated->box.w;
        this->associated->box.leftUp = pos;
        this->associated->box.leftUp.x += 0.75f * myCard->associated->box.w * this->skillPos;
        this->onSkill = true;
    }

    // Indíce do controle
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    int xMove = input.IsKeyPress(buttonRight[cId]) - input.IsKeyPress(buttonLeft[cId]);
    if (xMove + this->skillPos >= 0 && xMove + this->skillPos <= 1) {
        this->skillPos += xMove;
        this->associated->box.leftUp.x += 0.75f * myCard->associated->box.w * xMove;
    }

    if (input.IsKeyPress(buttonAttack[cId])) {
        this->selectedSkill = this->myCard->skills[this->skillPos];
    }
}


bool PlayerHand::CastSkill() {
    int cId = this->playerNum - 1;
    InputManager &input = InputManager::GetInstance();
    if (input.IsKeyPress(buttonAttack[cId])) {
        return CardSkill::Run(this->selectedSkill, this->pos, this->myCard, this->lastTarget);
    }
    return false;
}