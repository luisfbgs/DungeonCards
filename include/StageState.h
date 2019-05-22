#ifndef STAGESTATE
#define STAGESTATE

#include <memory>
#include "State.h"

class StageState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    
private:
};

#endif