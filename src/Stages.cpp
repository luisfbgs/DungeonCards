#include <memory>

#include "Game.h"
#include "Player.h"
#include "Stages.h"
#include "StageState.h"
#include "Action.h"
#include "GameData.h"

void Stages::CreatePlayers(std::shared_ptr<StageState> newStage) {
    for(int i = 1; i <= GameData::playersCount; i++) {
        std::shared_ptr<GameObject> playerGO = std::make_shared<GameObject>();
        std::shared_ptr<Player> newPlayer = std::make_shared<Player>(playerGO, PLAYER_PATH + std::to_string(i) + ".png", i);
        playerGO->AddComponent(newPlayer);
        newStage->AddObject(playerGO);
        Action::Move(newStage->board.GetCard(i).get(), {i - (GameData::playersCount > 2), 1});
        GameData::players.push_back(newPlayer);
    }
}


void Stages::InitStage1() {
    std::shared_ptr<StageState> newStage = std::make_shared<StageState>();
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria duas cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "1.png"), -1);
    GameData::enemies.push_back(newStage->board.GetCard(-1));
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    newStage->AddCard(std::string(ENEMY_PATH "2.png"), -2);
    GameData::enemies.push_back(newStage->board.GetCard(-2));
    Action::Move(newStage->board.GetCard(-2).get(), {2, 0});
    GameData::enemyCount = 2;

    // Cria as cartas dos jogadores
    Stages::CreatePlayers(newStage);
    for(auto player : GameData::players) {
        newStage->AddObject(player.lock()->playerHand->associated);
    }
}

void Stages::InitStage2() {
    std::shared_ptr<StageState> newStage = std::make_shared<StageState>();
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria tres cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "3.png"), -1);
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    GameData::enemies.push_back(newStage->board.GetCard(-1));
    newStage->AddCard(std::string(ENEMY_PATH "4.png"), -2);
    GameData::enemies.push_back(newStage->board.GetCard(-2));
    Action::Move(newStage->board.GetCard(-2).get(), {2, 0});
    newStage->AddCard(std::string(ENEMY_PATH "5.png"), -3);
    Action::Move(newStage->board.GetCard(-3).get(), {3, 0});
    GameData::enemies.push_back(newStage->board.GetCard(-3));
    GameData::enemyCount = 3;

    // Cria as cartas dos jogadores
    Stages::CreatePlayers(newStage);
    
    for(auto player : GameData::players) {
        newStage->AddObject(player.lock()->playerHand->associated);
    }
}

void Stages::InitStage3() {
    std::shared_ptr<StageState> newStage = std::make_shared<StageState>();
    Game::GetInstance().Push(newStage);
    newStage->Start();
    // Cria tres cartas de inimigo
    newStage->AddCard(std::string(ENEMY_PATH "6.png"), -1);
    Action::Move(newStage->board.GetCard(-1).get(), {1, 0});
    Action::Move(newStage->board.GetCard(-1).get(), {0, 0});
    GameData::enemies.push_back(newStage->board.GetCard(-1));
    newStage->AddCard(std::string(ENEMY_PATH "7.png"), -2);
    Action::Move(newStage->board.GetCard(-2).get(), {1, 0});
    GameData::enemies.push_back(newStage->board.GetCard(-2));
    newStage->AddCard(std::string(ENEMY_PATH "8.png"), -3);
    GameData::enemies.push_back(newStage->board.GetCard(-3));
    Action::Move(newStage->board.GetCard(-3).get(), {2, 0});
    newStage->AddCard(std::string(ENEMY_PATH "9.png"), -4);
    Action::Move(newStage->board.GetCard(-4).get(), {3, 0});
    GameData::enemies.push_back(newStage->board.GetCard(-4));
    GameData::enemyCount = 4;

    // Cria as cartas dos jogadores
    Stages::CreatePlayers(newStage);
    
    for(auto player : GameData::players) {
        newStage->AddObject(player.lock()->playerHand->associated);
    }
}