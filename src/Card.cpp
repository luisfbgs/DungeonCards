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
#include "Sound.h"

Card::Card(std::shared_ptr<GameObject> associated, std::string file, int num, int hp, int attackPower) : Component(associated),
                                                                sprite(associated, file),
                                                                lifeBar(associated), skillIcon0(associated), skillIcon1(associated) {
    this->hp = hp;
    this->isDead = false;
    this->sizeW = this->sizeH = 1;
    this->pos = {0, 0};
    this->playerNum = num;
    this->acted = false;
    this->attackPower = attackPower;
    this->myAttibutes = clear;

    if(this->playerNum > 0) {
        // Pega o id das habilidades, baseado na carta utilizada
        int skillId = file[file.size() - 5] - '0';
        this->skills[0] = skillId * 2;
        this->skills[1] = skillId * 2 - 1;
        this->skillIcon0.Open(SKILL_PATH + std::to_string(skills[0]) + "l.png");
        this->skillIcon1.Open(SKILL_PATH + std::to_string(skills[1]) + "r.png");
    }

    this->angle = randReal(-2.0f, 2.0f);
    this->sprite.SetAngle(this->angle);
    this->lifeBar.Open(LIFE_PATH + std::to_string(hp) + ".png");
    this->SetScale();
}

void Card::Update(int dt) {
    (void)dt;

    if(!this->isDead) {
        if(this->hp <= 0) {
            if(GameData::runningAnimations == 0) {
                if(this->playerNum < 0) {
                    GameData::enemyCount--;
                }
                this->sprite.Open(IMG_PATH "cardBack.png");
                this->SetScale();
                this->isDead = true;
            }
            this->lifeBar.hidden = true;
            if(this->playerNum > 0) {
                this->skillIcon0.hidden = true;
                this->skillIcon1.hidden = true;
            }
            return;
        }
        this->lifeBar.Open(LIFE_PATH + std::to_string(hp) + ".png");
        
        if(TurnState::turnEnded) {
            return;
        }
        if(TurnState::current != this->lastActed ){
            this->acted = false;
        }

        // Caso a carta seja inimigo, causa 3 de dano a um player aleatório
        if(this->playerNum < 0 && TurnState::current == EnemyAttack && !this->acted){
            std::vector<Card*> targets;
            GameData::AddAlivePlayers(targets);
            if(targets.size()) {
                Card* target = targets[randInt(0, targets.size() - 1)];
                if(Action::Attack(this, this->attackPower, target->playerNum)) {
                    this->acted = true;
                    this->lastActed = TurnState::current;
                }
            }
        }
    }
}

void Card::Render() {
    this->sprite.Render();
    this->lifeBar.Render();
    if(this->playerNum > 0) {
        this->skillIcon0.Render();
        this->skillIcon1.Render();
    }
}

bool Card::Is(const std::string &type) {
    return type == "Card";
}

// Coloca o tamanho do sprite pra ser igual o da célula
void Card::SetScale() {
    
    // Calcula escala para carta se ajustar ao tabuleiro
    Board &board = Board::GetInstance();
    float cellW = board.GetCellW(), cellH = board.GetCellH();

    float spriteW = this->sprite.GetWidth();
    float spriteH = this->sprite.GetHeight();
    this->scale = std::min(cellW / 1.13f / spriteW, cellH / 1.13f / spriteH);
    
    // Ajusta o tamanho da carta
    this->sprite.SetScale(this->scale, this->scale);
    
    // Ajusta o tamanho da barra de vida
    if(this->lifeBar.IsOpen()) {
        this->lifeBar.SetScale(this->sprite.GetWidthS() / this->lifeBar.GetWidth(), this->sprite.GetHeightS() / this->lifeBar.GetHeight());
        this->lifeBar.SetAngle(this->angle);
    }

    if(this->playerNum > 0){
        // Ajusta tamanhos dos icones de skill
        if(this->skillIcon0.IsOpen()) {
            this->skillIcon0.SetScale(this->sprite.GetWidthS() / this->skillIcon0.GetWidth(), this->sprite.GetHeightS() / this->skillIcon0.GetHeight());
            this->skillIcon0.SetAngle(this->angle);
        }
        if(this->skillIcon1.IsOpen()) {
            this->skillIcon1.SetScale(this->sprite.GetWidthS() / this->skillIcon1.GetWidth(), this->sprite.GetHeightS() / this->skillIcon1.GetHeight());
            this->skillIcon1.SetAngle(this->angle);
        }
    }
}

int Card::GetNum() {
    return this->playerNum;
}

int Card::_Damage(int damage) {
    if (damage < 0) {
        return this->_Heal(-damage);
    }
    else if (damage > 0) {
        damage = (this->myAttibutes & immune) ? 0 : damage;
        this->hp -= damage / ((this->myAttibutes & halvesDamage) ? 2 : 1);
        
        // Som de atacado
        Sound::PlaySound("hit.wav");
        // Adiciona animação de dano na carta
        std::shared_ptr<GameObject> damageAniGO = std::make_shared<GameObject>();
        std::shared_ptr<Animation::Damage> damageAni = std::make_shared<Animation::Damage>(damageAniGO, this);
        damageAniGO->AddComponent(damageAni);
        Game::GetInstance().GetCurrentState().AddObject(damageAniGO);
    }
    return this->hp;
}

int Card::_Heal(int hp) {
    if(hp < 0) {
        return this->_Damage(-hp);
    }
    else if(hp > 0) {
        auto aux = this->hp+hp;
        if (aux > Card::MAX_LIFE) {
            this->hp = MAX_LIFE;
        }
        else {
            this->hp = aux;
        }
        // Adiciona animação de cura na carta
        Sound::PlaySound("healing.wav");
        std::shared_ptr<GameObject> healAniGO = std::make_shared<GameObject>();
        std::shared_ptr<Animation::Heal> healAni = std::make_shared<Animation::Heal>(healAniGO, this);
        healAniGO->AddComponent(healAni);
        Game::GetInstance().GetCurrentState().AddObject(healAniGO);
    }
    return this->hp;
}

int Card::GetAttackPower() {
    return this->attackPower;
}

Vec2Int Card::GetPos() {
    return this->pos;
}
