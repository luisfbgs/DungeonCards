#include "Game.h"
#include "TitleState.h"

int main (int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    Game::width = 1600;
    Game::height = 900;
    Game::GetInstance().Push(new TitleState());
    Game::GetInstance().Run();

    return 0;
}
