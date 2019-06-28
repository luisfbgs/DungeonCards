#include <memory>
#include <string>
#include <cstdio>

#include "StageState2.h"
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
#include "Music.h"

StageState2::StageState2() : board(Board::GetInstance()) {
    GameData::enemyCount = 3;
}

StageState2::~StageState2() {
    this->board.Reset();
}

void StageState2::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string(IMG_PATH "board.png")));
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);

    this->AddObject(bgGO);

    // Criar tabuleiro
    this->board.Init(2, 4, bgSprite->GetWidthS(), bgSprite->GetHeightS());

    // Cria três cartas de inimigo
    this->AddCard(std::string(ENEMY_PATH "3.png"), -1); Action::Move(this->board.GetCard(-1).get(), {1, 0});
    this->AddCard(std::string(ENEMY_PATH "4.png"), -2); Action::Move(this->board.GetCard(-2).get(), {2, 0});
    this->AddCard(std::string(ENEMY_PATH "5.png"), -3); Action::Move(this->board.GetCard(-3).get(), {3, 0});

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

    // Toca musica de batalha.
    this->music.Open(AUDIO_PATH "battle.mpeg");
    this->music.Play(-1);
}

void StageState2::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    // Verificar se o usuário deseja fechar o jogo
    this->quitRequested = input.QuitRequested() || input.IsKeyPress(ESCAPE_KEY);
    if(GameData::enemyCount == 0) {
        this->quitRequested = true;
        GameData::stagesBeated++;
    }
}

void StageState2::Render() {
    this->RenderArray();
}

void StageState2::Start() {
    this->LoadAssets();
    this->StartArray();
}

int StageState2::AddCard(std::string file, int num) {
    GameObject *playerCard = new GameObject();
    std::shared_ptr<Card> card(new Card(*playerCard, file, num));
    playerCard->AddComponent(card);

    this->AddObject(playerCard);
    return this->board.AddCard(card);
}

void StageState2::Pause() {
    this->music.Stop();
}

void StageState2::Resume() {
    this->music.Play(0);
}

int StageState2::AddPlayerHand(int num, std::string file) {
    GameObject *playerHandGO = new GameObject();
    std::shared_ptr<PlayerHand> playerHand(new PlayerHand(*playerHandGO, num, file));
    playerHandGO->AddComponent(playerHand);
    this->AddObject(playerHandGO);
    return ++GameData::playersCnt;
}