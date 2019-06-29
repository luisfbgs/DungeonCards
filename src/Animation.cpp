#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Sprite.h"
#include "Animation.h"
#include "GameData.h"

namespace Animation {
    Damage::Damage(GameObject &associated, Card *target) : Component(associated) {
        GameData::runningAnimations++;
        this->damageSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("damage.png")));
        this->damageSprite->SetAngle(target->angle);
        this->damageSprite->SetScale(target->scale, target->scale);
        this->associated.box.leftUp = target->associated.box.leftUp;
        this->associated.AddComponent(damageSprite);
        
        this->animationTimer.Restart();
    }

    Damage::~Damage() {
        GameData::runningAnimations--;
    }

    bool Damage::Is(const std::string &type) {
        return type == "DamageAnimation";
    }

    void Damage::Render() {
    }

    void Damage::Update(int dt) {
        this->animationTimer.Update(dt);
        // Alterna entre aparecer e sumir a cada 200 ms
        if(((this->animationTimer.Get() / 200) & 1) == this->damageSprite->hidden) {
            this->damageSprite->hidden ^= 1;
        }
        // Acaba após 800s
        if(this->animationTimer.Get() > 800) {
            this->associated.RequestDelete();
        }
    }

    Heal::Heal(GameObject &associated, Card *target) : Component(associated) {
        GameData::runningAnimations++;
        this->healSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("heal.png")));
        this->healSprite->SetAngle(target->angle);
        this->healSprite->SetScale(target->scale, target->scale);
        this->associated.box.leftUp = target->associated.box.leftUp;
        this->associated.AddComponent(healSprite);
        
        this->animationTimer.Restart();
    }

    Heal::~Heal() {
        GameData::runningAnimations--;
    }

    bool Heal::Is(const std::string &type) {
        return type == "HealAnimation";
    }

    void Heal::Render() {
    }

    void Heal::Update(int dt) {
        this->animationTimer.Update(dt);
        // Acaba após 800s
        if(this->animationTimer.Get() > 800) {
            this->associated.RequestDelete();
        }
    }
}