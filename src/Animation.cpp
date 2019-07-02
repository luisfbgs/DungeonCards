#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Game.h"
#include "Sprite.h"
#include "Event.h"
#include "Animation.h"
#include "GameData.h"

DamageAnimation::DamageAnimation(std::shared_ptr<GameObject> associated, Card *target) : Component(associated) {
    GameData::runningAnimations++;
    this->damageSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("damage.png")));
    this->damageSprite->SetAngle(target->angle);
    this->damageSprite->SetScale(target->scale, target->scale);
    this->associated->box.leftUp = target->associated->box.leftUp;
    this->associated->AddComponent(damageSprite);
    
    this->animationTimer.Restart();
}

DamageAnimation::~DamageAnimation() {
    GameData::runningAnimations--;
}

bool DamageAnimation::Is(const std::string &type) {
    return type == "DamageAnimation";
}

void DamageAnimation::Render() {
}

void DamageAnimation::Update(int dt) {
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

HealAnimation::HealAnimation(std::shared_ptr<GameObject> associated, Card *target) : Component(associated) {
    GameData::runningAnimations++;
    this->healSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("heal.png")));
    this->healSprite->SetAngle(target->angle);
    this->healSprite->SetScale(target->scale, target->scale);
    this->associated->box.leftUp = target->associated->box.leftUp;
    this->associated->AddComponent(healSprite);
    
    this->animationTimer.Restart();
}

HealAnimation::~HealAnimation() {
    GameData::runningAnimations--;
}

bool HealAnimation::Is(const std::string &type) {
    return type == "HealAnimation";
}

void HealAnimation::Render() {
}

void HealAnimation::Update(int dt) {
    this->animationTimer.Update(dt);
    // Acaba após 800s
    if(this->animationTimer.Get() > 800) {
        this->associated->RequestDelete();
    }
}

EventAnimation::EventAnimation(std::shared_ptr<GameObject> associated, int eventId) : Component(associated) {
    GameData::runningAnimations++;
    this->eventSprite = std::shared_ptr<Sprite>(new Sprite(associated, std::string(EVENT_PATH "Back.png")));
    this->eventSprite->SetScale(Game::heightS / 2 / eventSprite->GetHeightS(),
        Game::heightS / 2 / eventSprite->GetHeightS());
    this->associated->AddComponent(eventSprite);
    this->associated->box.leftUp = {Game::widthS - eventSprite->GetWidthS() * 1.1f, Game::heightS - eventSprite->GetHeightS() * 1.1f};

    this->eventId = eventId;
    this->onTarget = false;
    this->turnDown = true;
    this->animationTimer.Restart();
}

EventAnimation::~EventAnimation() {
    GameData::runningAnimations--;
}

bool EventAnimation::Is(const std::string &type) {
    return type == "EventAnimation";
}

void EventAnimation::Render() {
}

void EventAnimation::Update(int dt) {
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
                Event::ChooseEvent(eventId);
            }
        }
    }
}