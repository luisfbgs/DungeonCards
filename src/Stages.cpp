#include <memory>

#include "Game.h"
#include "Player.h"
#include "Stages.h"
#include "StageState.h"
#include "Action.h"
#include "GameData.h"

void Stages::InitStage1() {
    std::shared_ptr<StageState> newStage(new StageState());
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria duas cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "1.png"), -1);
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    newStage->AddCard(std::string(ENEMY_PATH "2.png"), -2);
    Action::Move(newStage->board.GetCard(-2).get(), {2, 0});
    GameData::enemyCount = 2;

    // Cria as cartas dos jogadores
    for(int i = 1; i <= GameData::playersCount; i++) {
        std::shared_ptr<GameObject> playerGO(new GameObject());
        std::shared_ptr<Player> newPlayer(new Player(playerGO, PLAYER_PATH + std::to_string(i) + ".png", i));
        playerGO->AddComponent(newPlayer);
        newStage->AddObject(playerGO);
        Action::Move(newStage->board.GetCard(i).get(), {i, 1});
        GameData::players.push_back(newPlayer);
    }
    for(auto player : GameData::players) {
        newStage->AddObject(player.lock()->playerHand->associated);
    }
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
    newStage->AddCard(std::string(ENEMY_PATH "5.png"), -3);
    Action::Move(newStage->board.GetCard(-3).get(), {3, 0});
    GameData::enemyCount = 3;

    // Cria as cartas dos jogadores
    for(int i = 1; i <= GameData::playersCount; i++) {
        std::shared_ptr<GameObject> playerGO(new GameObject());
        std::shared_ptr<Player> newPlayer(new Player(playerGO, PLAYER_PATH + std::to_string(i) + ".png", i));
        playerGO->AddComponent(newPlayer);
        newStage->AddObject(playerGO);
        Action::Move(newStage->board.GetCard(i).get(), {i, 1});
        GameData::players.push_back(newPlayer);
    }

    for(auto player : GameData::players) {
        newStage->AddObject(player.lock()->playerHand->associated);
    }
}