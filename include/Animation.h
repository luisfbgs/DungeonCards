#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Card.h"
#include "Sprite.h"
#include "Timer.h"

class DamageAnimation : public Component {
public:
    DamageAnimation(std::shared_ptr<GameObject> associated, Card *target);
    ~DamageAnimation();
    void Update(int dt);
    bool Is(const std::string &type);
    void Render();
    std::shared_ptr<Sprite> damageSprite;
    Timer animationTimer;
};

class HealAnimation : public Component {
public:
    HealAnimation(std::shared_ptr<GameObject> associated, Card *target);
    ~HealAnimation();
    void Update(int dt);
    bool Is(const std::string &type);
    void Render();
    std::shared_ptr<Sprite> healSprite;
    Timer animationTimer;
};

class EventAnimation : public Component {
public:
    EventAnimation(std::shared_ptr<GameObject> associated, int eventId);
    ~EventAnimation();
    void Update(int dt);
    bool Is(const std::string &type);
    void Render();
    std::shared_ptr<Sprite> eventSprite;
    int eventId;
    Timer animationTimer;
    bool onTarget;
    bool turnDown;
};