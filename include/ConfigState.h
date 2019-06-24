#pragma once

#include <vector>

#include "State.h"

class ConfigState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    std::vector<std::pair<int, int>> resolutionList;
    std::pair<int, int> resolution;
};

