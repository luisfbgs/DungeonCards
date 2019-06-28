#include <memory>
#include <string>
#include <cstdio>

#include "StageState.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameData.h"
#include "Game.h"
#include "Board.h"
#include "Card.h"
#include "Vec2Int.h"
#include "Camera.h"
#include "Action.h"
#include "TurnTimer.h"
#include "PlayerHand.h" 

StageState::StageState() : board(Board::GetInstance()) {
    GameData::enemyCount = 2;
}

StageState::~StageState() {
    this->board.Reset();
}

void StageState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string(STAGE_PATH "tutorial.jpg")));
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);

    this->AddObject(bgGO);

    // Criar tabuleiro
    this->board.Init(2, 4, bgSprite->GetWidthS(), bgSprite->GetHeightS());

    // Cria duas cartas de inimigo
    this->AddCard(std::string(ENEMY_PATH "1.png"), -1); Action::Move(this->board.GetCard(-1).get(), {1, 0});
    this->AddCard(std::string(ENEMY_PATH "2.png"), -2); Action::Move(this->board.GetCard(-2).get(), {2, 0});

    // Cria a carta do jogador 1
    this->AddCard(std::string(PLAYER_PATH "1.png"), 1); Action::Move(this->board.GetCard(1).get(), {1, 1});

    this->AddCard(std::string(PLAYER_PATH "2.png"), 2);Action::Move(this->board.GetCard(2).get(), {2, 2});

    // Cria um circulo para representar o timer
    GameObject *timerGO = new GameObject();
    std::shared_ptr<TurnTimer> turnTimer(new TurnTimer(*timerGO));
    timerGO->AddComponent(turnTimer);
    this->AddObject(timerGO);

    // Adiciona cursores aos jogadores
    this->AddPlayerHand(1, std::string(CURSOR_PATH "1.png"));
    this->AddPlayerHand(2, std::string(CURSOR_PATH "2.png"));
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    // Verificar se o usuário deseja fechar o jogo
    this->quitRequested |= input.QuitRequested() || input.IsKeyPress(ESCAPE_KEY);
    if(GameData::enemyCount == 0) {
        this->quitRequested = true;
        GameData::stagesBeated++;
    }
}

void StageState::Render() {
    this->RenderArray();
}

void StageState::Start() {
    this->LoadAssets();
    this->StartArray();
}

int StageState::AddCard(std::string file, int num) {
    GameObject *playerCard = new GameObject();
    std::shared_ptr<Card> card(new Card(*playerCard, file, num));
    playerCard->AddComponent(card);

    this->AddObject(playerCard);
    return this->board.AddCard(card);
}

void StageState::Pause() {
    GameData::playersCnt = 0;
}

void StageState::Resume() {
}

int StageState::AddPlayerHand(int num, std::string file) {
    GameObject *playerHandGO = new GameObject();
    std::shared_ptr<PlayerHand> playerHand(new PlayerHand(*playerHandGO, num, file));
    playerHandGO->AddComponent(playerHand);
    this->AddObject(playerHandGO);
    return ++GameData::playersCnt;
}