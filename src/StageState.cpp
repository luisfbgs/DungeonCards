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

StageState::StageState() : board(Board::GetInstance()) {
    GameData::turn = 0;
}

StageState::~StageState() {
    this->board.Reset();
}

void StageState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string("assets/img/board.jpeg")));
    float bgScale = std::min((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);

    float blackBarX = (float)Game::GetInstance().GetWidth() - bgSprite->GetWidthS();
    float blackBarY = (float)Game::GetInstance().GetHeight() - bgSprite->GetHeightS();
    Camera::pos = {-blackBarX / 2, -blackBarY / 2};

    this->AddObject(bgGO);

    // Criar tabuleiro
    this->board.Init(2, 4, bgSprite->GetWidthS(), bgSprite->GetHeightS());

    // Cria duas cartas de inimigo
    this->AddCard(std::string("assets/img/player.jpeg"), -1);
    Action::Move(this->board.GetCard(-1).get(), {1, 0});
    this->AddCard(std::string("assets/img/player.jpeg"), -2);
    Action::Move(this->board.GetCard(-2).get(), {2, 0});

    // Cria a carta do jogador 1
    this->AddCard(std::string("assets/img/player.jpg"), 1);
    Action::Move(this->board.GetCard(1).get(), {1, 1});

    // Cria um circulo para representar o timer
    GameObject *timerGO = new GameObject();
    std::shared_ptr<TurnTimer> turnTimer(new TurnTimer(*timerGO, std::string("assets/img/circle.png")));
    timerGO->AddComponent(turnTimer);
    this->AddObject(timerGO);
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    this->quitRequested = input.IsKeyPress(ESCAPE_KEY);
    // Verificar se o usuário deseja fechar o jogo
    GameData::quitAll = input.QuitRequested();
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
}

void StageState::Resume() {
}