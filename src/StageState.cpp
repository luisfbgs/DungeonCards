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
}

StageState::~StageState() {
    this->board.Reset();
}

void StageState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string(IMG_PATH "board.png")));
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
    this->AddCard(std::string(IMG_PATH "lucario.jpg"), -1); Action::Move(this->board.GetCard(-1).get(), {1, 0});
    this->AddCard(std::string(IMG_PATH "lucario.jpg"), -2); Action::Move(this->board.GetCard(-2).get(), {2, 0});

    // Cria a carta do jogador 1
    this->AddCard(std::string(PLAYER_PATH "1.jpg"), 1); Action::Move(this->board.GetCard(1).get(), {1, 1});

    this->AddCard(std::string(PLAYER_PATH "2.jpg"), 2);Action::Move(this->board.GetCard(2).get(), {2, 2});

    // Cria um circulo para representar o timer
    GameObject *timerGO = new GameObject();
    std::shared_ptr<TurnTimer> turnTimer(new TurnTimer(*timerGO));
    timerGO->AddComponent(turnTimer);
    this->AddObject(timerGO);

    // Adiciona cursores aos jogadores
    this->AddPlayerHand(1, std::string(IMG_PATH "circle.png"));
    this->AddPlayerHand(2, std::string(IMG_PATH "square.png"));
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