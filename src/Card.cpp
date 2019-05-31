#include <string>
#include <cstdio>

#include "GameObject.h"
#include "GameData.h"
#include "Component.h"
#include "Common.h"
#include "Card.h"
#include "Board.h"
#include "Vec2.h"
#include "Vec2Int.h"
#include "InputManager.h"

Card::Card(GameObject &associated, std::string file, int num, int hp) : Component(associated),
                                                                sprite(associated, file),
                                                                lifeBar(associated, std::string("assets/img/lifeBar.png")) {
    this->hp = hp;
    this->szW = this->szH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->hasMoved = false;
}

void Card::Update(int dt) {
    (void)dt;

    if(this->hp <= 0) {
        this->associated.RequestDelete();
        return;
    }

    this->lifeBar.SetScale(this->lifeBarSize * this->hp / 100,
                           this->lifeBarSize);

    if((playerNum > 0) == GameData::turn){
        this->hasMoved = false;
    }

    if(playerNum > 0 && !GameData::turn && !this->hasMoved) {
        InputManager &input = InputManager::GetInstance();
        // Mover a carta
        int yMove = input.IsKeyPress('s') - input.IsKeyPress('w');
        int xMove = input.IsKeyPress('d') - input.IsKeyPress('a');
        if(xMove || yMove) {
            if(Action::Move(this, {xMove, yMove}, this->pos)) {
                this->hasMoved = true;
                return;
            }
        }
        // Causar 5 de dano a um inimigo
        for(int key : input.GetAllKeys()) {
            if(key >= '1' && key <= '9') {
                if(Action::Attack(this, 20, -(key - '0'))) {
                    this->hasMoved = true;
                    return;
                }
            }
        }
    }
    else if(playerNum < 0 && GameData::turn && !this->hasMoved){
        if(Action::Attack(this, 9, randInt(1, GameData::playersCnt))) {
            this->hasMoved = true;
        }
    }
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

int Card::GetNum() {
    return this->playerNum;
}
