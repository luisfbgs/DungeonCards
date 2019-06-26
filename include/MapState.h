#pragma once

#include <memory>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Vec2.h"

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
    GameObject *cursor;
    std::vector<Vec2> stages;
};

