#include <memory>

#include "Game.h"
#include "TitleState.h"
#include "GameData.h"

int main (int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    Game::width = 1280;
    Game::height = 720;
    do {
        GameData::restart = false;
        GameData::quitAll = false;
        Game::GetInstance().Push(std::shared_ptr<State>(new TitleState()));
        Game::GetInstance().Run();
        Game::GetInstance().~Game();
    } while(GameData::restart);

    return 0;
}
