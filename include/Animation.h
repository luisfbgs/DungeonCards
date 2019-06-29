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
        ~Damage();
        void Update(int dt);
        bool Is(const std::string &type);
        void Render();
        std::shared_ptr<Sprite> damageSprite;
        Timer animationTimer;
    };

    class Heal : public Component {
    public:
        Heal(GameObject &associated, Card *target);
        ~Heal();
        void Update(int dt);
        bool Is(const std::string &type);
        void Render();
        std::shared_ptr<Sprite> healSprite;
        Timer animationTimer;
    };
}