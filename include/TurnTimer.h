#pragma once

#include <string>

#include "Component.h"
#include "Timer.h"
#include "Sprite.h"

class TurnTimer : public Component {
public:
    TurnTimer(std::shared_ptr<GameObject> associated);
    void Render();
    void SetScale();
    void Update(int dt);
    bool Is(const std::string &type);

private:
    const int kTurnLength = 7000;
    std::shared_ptr<GameObject> timerGO;
    std::shared_ptr<Sprite> timerSprite;
    std::shared_ptr<GameObject> pointerGO;
    std::shared_ptr<Sprite> pointerSprite;
    Timer timer;
};

