#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Sprite.h"
#include "Animation.h"

namespace Animation {
    Damage::Damage(GameObject &associated, Card *target) : Component(associated) {
        this->damageSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("damage.png")));
        this->damageSprite->SetAngle(target->angle);
        this->damageSprite->SetScale(target->scale, target->scale);
        this->associated.box.leftUp = target->associated.box.leftUp;
        this->associated.AddComponent(damageSprite);
        
        this->animationTimer.Restart();
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
        // Acaba após 1s
        if(this->animationTimer.Get() > 1000) {
            this->associated.RequestDelete();
        }
    }
}