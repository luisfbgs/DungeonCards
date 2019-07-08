#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Game.h"
#include "Sprite.h"
#include "Event.h"
#include "Animation.h"
#include "GameData.h"

Animation::Damage::Damage(std::shared_ptr<GameObject> associated, Card *target) : Component(associated) {
    GameData::runningAnimations++;
    this->damageSprite = std::make_shared<Sprite>(associated, ANIMATION_PATH + std::string("damage.png"));
    this->damageSprite->SetAngle(target->angle);
    this->damageSprite->SetScale(target->sprite.GetWidthS() / this->damageSprite->GetWidthS(), target->sprite.GetHeightS() / this->damageSprite->GetHeightS());
    this->associated->box.leftUp = target->associated->box.leftUp;
    this->associated->AddComponent(damageSprite);
    
    this->animationTimer.Restart();
}

Animation::Damage::~Damage() {
    GameData::runningAnimations--;
}

bool Animation::Damage::Is(const std::string &type) {
    return type == "DamageAnimation";
}

void Animation::Damage::Render() {
}

void Animation::Damage::Update(int dt) {
    this->animationTimer.Update(dt);
    // Alterna entre aparecer e sumir a cada 200 ms
    if(((this->animationTimer.Get() / 200) & 1) == this->damageSprite->hidden) {
        this->damageSprite->hidden ^= 1;
    }
    // Acaba após 800s
    if(this->animationTimer.Get() > 800) {
        this->associated->RequestDelete();
    }
}

Animation::Heal::Heal(std::shared_ptr<GameObject> associated, Card *target) : Component(associated) {
    GameData::runningAnimations++;
    this->healSprite = std::make_shared<Sprite>(associated, ANIMATION_PATH + std::string("heal.png"))   ;
    this->healSprite->SetAngle(target->angle);
    this->healSprite->SetScale(target->sprite.GetWidthS() / this->healSprite->GetWidthS(), target->sprite.GetHeightS() / this->healSprite->GetHeightS());
    this->associated->box.leftUp = target->associated->box.leftUp;
    this->associated->AddComponent(healSprite);
    
    this->animationTimer.Restart();
}

Animation::Heal::~Heal() {
    GameData::runningAnimations--;
}

bool Animation::Heal::Is(const std::string &type) {
    return type == "HealAnimation";
}

void Animation::Heal::Render() {
}

void Animation::Heal::Update(int dt) {
    this->animationTimer.Update(dt);
    // Acaba após 800s
    if(this->animationTimer.Get() > 800) {
        this->associated->RequestDelete();
    }
}

Animation::Event::Event(std::shared_ptr<GameObject> associated, int eventId) : Component(associated) {
    GameData::runningAnimations++;
    this->eventSprite = std::make_shared<Sprite>(Sprite(associated, std::string(EVENT_PATH "Back.png")));
    this->eventSprite->SetScale(Game::heightS / 2 / eventSprite->GetHeightS(),
        Game::heightS / 2 / eventSprite->GetHeightS());
    this->associated->AddComponent(eventSprite);
    this->associated->box.leftUp = {Game::widthS - eventSprite->GetWidthS() * 1.1f, Game::heightS - eventSprite->GetHeightS() * 1.1f};

    this->eventId = eventId;
    this->onTarget = false;
    this->turnDown = true;
    this->animationTimer.Restart();
}

Animation::Event::~Event() {
    GameData::runningAnimations--;
}

bool Animation::Event::Is(const std::string &type) {
    return type == "EventAnimation";
}

void Animation::Event::Render() {
}

void Animation::Event::Update(int dt) {
    if(!this->onTarget) {
        Vec2 target = {Game::widthS / 2, Game::heightS / 2};
        Vec2 move = target - this->associated->box.Center();
        if(move.Length() < (move.Norm() * dt * Game::heightS / 900).Length()) {
            this->associated->box.leftUp += move;
            this->onTarget = true;
        }
        else{
            this->associated->box.leftUp += move.Norm() * dt * Game::heightS / 900;
        }
    }
    else {
        this->animationTimer.Update(dt);
        // Fica 200 ms com o verso para cima depois de atingir o centro da tela
        if(this->animationTimer.Get() >= 200) {
            // Se estiver virado pra baixo vira a carta
            if(this->turnDown) {
                this->eventSprite->Open(EVENT_PATH + std::to_string(eventId) + ".png");
                this->turnDown = false;
            }
            // Animação acaba após 2s virada para cima
            if(this->animationTimer.Get() >= 2200) {
                this->associated->RequestDelete();
                // sobre um namespace para não dar conflito com o evento de animação
                ::Event::ChooseEvent(eventId);  
            }
        }
    }
}
