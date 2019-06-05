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
                                                                lifeBar(associated) {
    this->hp = hp;
    this->szW = this->szH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->acted = false;
}

void Card::Update(int dt) {
    (void)dt;

    if(this->hp <= 0) {
        this->associated.RequestDelete();
        return;
    }
    this->lifeBar.Open("assets/img/counter" + std::to_string(hp) + ".png");
    this->SetScale();

    if((playerNum > 0) == GameData::turn){
        this->acted = false;
    }

    if(playerNum > 0 && !GameData::turn && !this->acted) {
        InputManager &input = InputManager::GetInstance();
        // Mover a carta
        int yMove = input.IsKeyPress('s') - input.IsKeyPress('w');
        int xMove = input.IsKeyPress('d') - input.IsKeyPress('a');
        if(xMove || yMove) {
            if(Action::Move(this, {xMove, yMove}, this->pos)) {
                this->acted = true;
                return;
            }
        }
        // Causar 3 de dano a um inimigo
        for(int key : input.GetAllKeys()) {
            if(key >= '1' && key <= '9') {
                if(Action::Attack(this, 3, -(key - '0'))) {
                    this->acted = true;
                    return;
                }
            }
        }
    }
    else if(playerNum < 0 && GameData::turn && !this->acted){
        if(Action::Attack(this, 1, randInt(1, GameData::playersCnt))) {
            this->acted = true;
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
    float cellW = board.GetCellW(), cellH = board.GetCellH();

    // Ajusta o tamanho da carta
    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    float scale = std::min(cellW / spriteW, cellH / spriteH);
    this->sprite.SetScale(this->szW * scale, this->szH * scale);
    
    // Ajusta o tamanho da barra de vida
    if(this->lifeBar.IsOpen()) {
        spriteW = this->lifeBar.GetWidth();
        spriteH = this->lifeBar.GetHeight();
        scale = this->sprite.GetWidthS() / 2.3 / spriteW;
        this->lifeBar.SetScale(scale, scale);
    }
}

int Card::GetNum() {
    return this->playerNum;
}
