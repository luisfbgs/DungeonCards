#ifndef ACTIONMOVE
#define ACTIONMOVE

#include "Action.h"
#include "Vec2Int.h"

class ActionMove : public Action {
public:
    ActionMove();
    void Run(int idSource, Vec2Int pos, Vec2Int offSet = {0, 0});
private:
};

#endif