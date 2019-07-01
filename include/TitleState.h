#pragma once

#include <memory>

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Vec2.h"

class TitleState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    Music music;
private:
    enum Option {
        Continue,
        NewGame,
        Options,
        Quit
    };
    Option selectedOption;
    std::shared_ptr<GameObject> selectSpriteGO;
    std::shared_ptr<Sprite> selectSprite;
    int lastOption;
};

