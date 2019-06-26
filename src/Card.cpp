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
#include "TurnState.h"

Card::Card(GameObject &associated, std::string file, int num, int hp, int attackPower) : Component(associated),
                                                                sprite(associated, file),
                                                                lifeBar(associated) {
    this->hp = hp;
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->acted = false;
    this->attackPower = attackPower;
}

void Card::Update(int dt) {
    (void)dt;

    if(this->hp <= 0) {
        this->associated.RequestDelete();
        return;
    }
    this->lifeBar.Open("assets/img/counter" + std::to_string(hp) + ".png");
    this->SetScale();

    if(TurnState::current != this->lastActed ){
        this->acted = false;
    }

    // Caso a carta seja inimigo, causa 3 de dano a um player aleatório
    if(playerNum < 0 && TurnState::current == EnemyAttack && !this->acted){
        if(Action::Attack(this, this->attackPower, randInt(1, GameData::playersCnt))) {
            this->acted = true;
            this->lastActed = TurnState::current;
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
    this->sprite.SetScale(this->sizeW * scale, this->sizeH * scale);
    
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

int Card::_Damage(int damage) {
  if (damage < 0)
      return this->_Heal(-damage);
  else {
      this->hp -= damage;
  }
  return this->hp;
}
int Card::_Heal(int hp) {
  if(hp < 0) {
    return this->_Damage(hp);
  }
  else {
    this->hp = ((this->hp + hp) % MAX_LIFE + this->MAX_LIFE) % this->MAX_LIFE;
  }
  return this->hp;
}

int Card::GetAttackPower() {
    return this->attackPower;
}

Vec2Int Card::GetPos() {
    return this->pos;
}