#pragma once

#include <memory>
#include <vector>
#include "Sprite.h"
#include "State.h"
#include "GameObject.h"
#include "Vec2.h"
#include <string>
#include "Vec2Int.h"
#include "MapState.h"

class CongratsState : public State {
public:
    State * caller;
    ~CongratsState();
    CongratsState(State* caller);
    CongratsState();
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    std::shared_ptr<GameObject> backgroundGO;
    std::shared_ptr<Sprite> backgroundSprite;
};
