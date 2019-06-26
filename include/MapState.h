#pragma once

#include <memory>

#include "State.h"

class MapState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    int pos;
};

