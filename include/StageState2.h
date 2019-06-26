#pragma once

#include <memory>
#include <string>

#include "Timer.h"
#include "State.h"
#include "Board.h"

class StageState2 : public State {
public:
    StageState2();
    ~StageState2();
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    int AddCard(std::string file, int num);    
    void Pause();
    void Resume();
    Board* GetBoardPtr();
private:
    int AddPlayerHand(int num, std::string file);
    Board &board;
};


