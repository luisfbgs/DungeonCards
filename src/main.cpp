#include "Game.h"
#include "TitleState.h"

#include "Action.h"
#include "ActionMove.h"
#include <map>

int main (int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    Game::GetInstance().Push(new TitleState());
    Game::GetInstance().Run();

    return 0;
}
