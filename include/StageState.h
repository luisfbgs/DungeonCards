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
    void Pause();
    void Resume();
    int AddCard(std::string file);    
private:
    Board board;
};

#endif