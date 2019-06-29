#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Sprite.h"
#include "Timer.h"

namespace Animation {
    class Damage : public Component {
    public:
        Damage(GameObject &associated, Card *target);
        void Update(int dt);
        bool Is(const std::string &type);
        void Render();
        std::shared_ptr<Sprite> damageSprite;
        Timer animationTimer;
    };
}