#pragma once

#include <memory>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Music.h"

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
    std::shared_ptr<GameObject> cursor;
    std::vector<Vec2> stages;
    Music music;
};

