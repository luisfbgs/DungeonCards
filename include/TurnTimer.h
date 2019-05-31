#ifndef TURNTIMER
#define TURNTIMER

#include <string>

#include "Component.h"
#include "Timer.h"
#include "Sprite.h"

class TurnTimer : public Component {
public:
    TurnTimer(GameObject &associated, std::string file);
    void Render();
    void ResetScale();
    void Update(int dt);
    bool Is(const std::string &type);

private:
    Sprite timerSprite;
    Timer timer;
    float baseScale;
};

#endif