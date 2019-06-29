#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Sprite.h"
#include "Animation.h"

Animation::Damage::Damage(GameObject &associated, Card *target) : Component(associated) {
    this->damageSprite = std::shared_ptr<Sprite>(new Sprite(associated, ANIMATION_PATH + std::string("damage.png")));
    this->damageSprite->SetAngle(target->angle);
    this->damageSprite->SetScale(target->scale, target->scale);
    this->associated.box.leftUp = target->associated.box.leftUp;
    this->associated.AddComponent(damageSprite);
    
    this->animationTimer.Restart();
}

bool Animation::Damage::Is(const std::string &type) {
    return type == "DamageAnimation";
}

void Animation::Damage::Render() {
}

void Animation::Damage::Update(int dt) {
    this->animationTimer.Update(dt);
    if(this->animationTimer.Get() > 500) {
        this->associated.RequestDelete();
    }
}