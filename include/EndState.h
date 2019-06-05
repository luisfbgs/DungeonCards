#pragma once

#include "State.h"

class EndState : public State {
public:
    EndState();
    ~EndState();
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
};

