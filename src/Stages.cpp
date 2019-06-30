#include <memory>

#include "Game.h"
#include "Stages.h"
#include "StageState.h"
#include "Action.h"

void Stages::InitStage1() {
    std::shared_ptr<StageState> newStage(new StageState());
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria duas cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "1.png"), -1);
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    newStage->AddCard(std::string(ENEMY_PATH "2.png"), -2);
    Action::Move(newStage->board.GetCard(-2).get(), {2, 0});

    // Cria as cartas dos jogadores
    newStage->AddCard(std::string(PLAYER_PATH "1.png"), 1);
    Action::Move(newStage->board.GetCard(1).get(), {1, 1});
    newStage->AddCard(std::string(PLAYER_PATH "2.png"), 2);
    Action::Move(newStage->board.GetCard(2).get(), {2, 1});

    // Adiciona cursores aos jogadores
    newStage->AddPlayerHand(1, std::string(CURSOR_PATH "1.png"));
    newStage->AddPlayerHand(2, std::string(CURSOR_PATH "2.png"));
}

void Stages::InitStage2() {
    std::shared_ptr<StageState> newStage(new StageState());
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria duas cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "3.png"), -1);
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    newStage->AddCard(std::string(ENEMY_PATH "4.png"), -2);
    Action::Move(newStage->board.GetCard(-2).get(), {2, 0});
    newStage->AddCard(std::string(ENEMY_PATH "5.png"), -2);
    Action::Move(newStage->board.GetCard(-2).get(), {3, 0});

    // Cria as cartas dos jogadores
    newStage->AddCard(std::string(PLAYER_PATH "1.png"), 1);
    Action::Move(newStage->board.GetCard(1).get(), {1, 1});
    newStage->AddCard(std::string(PLAYER_PATH "2.png"), 2);
    Action::Move(newStage->board.GetCard(2).get(), {2, 1});

    // Adiciona cursores aos jogadores
    newStage->AddPlayerHand(1, std::string(CURSOR_PATH "1.png"));
    newStage->AddPlayerHand(2, std::string(CURSOR_PATH "2.png"));
}