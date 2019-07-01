#pragma once

#include <memory>
#include <string>

#include "Timer.h"
#include "State.h"
#include "Board.h"
#include "Music.h"

class StageState : public State {
public:
    ~StageState();
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    int AddCard(std::string file, int num);    
    void Pause();
    void Resume();
    Board* GetBoardPtr();
    Board &board;
    StageState();
private:
    Music music;
};


