#include <string>
#include <cstdio>

#include "Game.h"
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
#include "Animation.h"

Card::Card(GameObject &associated, std::string file, int num, int hp, int attackPower) : Component(associated),
                                                                sprite(associated, file),
                                                                lifeBar(associated) {
    this->hp = hp;
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->acted = false;
    this->attackPower = attackPower;
    this->angle = randReal(-2.0f, 2.0f);
    this->sprite.SetAngle(this->angle);

    // Calcula escala para carta se ajustar ao tabuleiro
    Board &board = Board::GetInstance();
    float cellW = board.GetCellW(), cellH = board.GetCellH();
    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    this->scale = std::min(cellW / 1.13f / spriteW, cellH / 1.13f / spriteH);
}

void Card::Update(int dt) {
    (void)dt;

    if(this->hp <= 0) {
        if(this->playerNum < 0) {
            GameData::enemyCount--;
        }
        this->associated.RequestDelete();
        return;
    }
    this->lifeBar.Open(LIFE_PATH + std::to_string(hp) + ".png");
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

    // Ajusta o tamanho da carta
    this->sprite.SetScale(this->sizeW * this->scale, this->sizeH * this->scale);
    
    // Ajusta o tamanho da barra de vida
    if(this->lifeBar.IsOpen()) {
        this->lifeBar.SetScale(this->sizeW * this->scale, this->sizeH * this->scale);
        this->lifeBar.SetAngle(this->angle);
    }
}

int Card::GetNum() {
    return this->playerNum;
}

int Card::_Damage(int damage) {
    if (damage < 0) {
        return this->_Heal(-damage);
    }
    else {
        this->hp -= damage;
        GameObject *damageAniGO = new GameObject();
        std::shared_ptr<Animation::Damage> damageAni(new Animation::Damage(*damageAniGO, this));
        damageAniGO->AddComponent(damageAni);
        Game::GetInstance().GetCurrentState().AddObject(damageAniGO);
    }
    return this->hp;
}

int Card::_Heal(int hp) {
    if(hp < 0) {
        return this->_Damage(-hp);
    }
    else {
        auto aux = this->hp+hp;
        if (aux > Card::MAX_LIFE) {
            this->hp = MAX_LIFE;
        }
        else {
            this->hp = aux;
        }
    }
    return this->hp;
}

int Card::GetAttackPower() {
    return this->attackPower;
}

Vec2Int Card::GetPos() {
    return this->pos;
}