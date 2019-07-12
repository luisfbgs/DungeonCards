#pragma once

#include <memory>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Vec2.h"
#include <string>
#include "Vec2Int.h"
#define TUTORIAL_PATH IMG_PATH "tutorial/"


class TutorialState : public State {
public:
    const static std::string prefix;
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    void NextScreen();
    void PrevScreen();
private:
    void _UpdateBackground();
    int curr;
    Vec2Int min_max_fileNumber;
    std::shared_ptr<GameObject> backgroundGO;
    std::shared_ptr<Sprite> backgroundSprite;
};
