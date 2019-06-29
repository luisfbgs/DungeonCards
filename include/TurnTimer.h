#pragma once

#include <string>

#include "Component.h"
#include "Timer.h"
#include "Sprite.h"

class TurnTimer : public Component {
public:
    TurnTimer(GameObject &associated);
    void Render();
    void SetScale();
    void Update(int dt);
    bool Is(const std::string &type);

private:
    const int kTurnLength = 1000;
    GameObject timerGO;
    Sprite timerSprite;
    GameObject pointerGO;
    Sprite pointerSprite;
    Timer timer;
};

