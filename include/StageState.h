#ifndef STAGESTATE
#define STAGESTATE

#include <memory>
#include <string>
#include "State.h"
#include "Board.h"

class StageState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    int AddCard(std::string file);    
    void Pause();
    void Resume();
    Board* GetBoardPtr();
    StageState();
private:
    Board &board;
};

#endif