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
#include "Music.h"

StageState::StageState() : board(Board::GetInstance()) {
}

StageState::~StageState() {
    for(auto i : this->objectArray) {
        i->RequestDelete();
    }
    this->objectArray.clear();
    this->board.Reset();
    GameData::players.clear();
    GameData::enemies.clear();
}

void StageState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(bgGO, std::string(STAGE_PATH "tutorial.jpg"));
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);


    // Criar tabuleiro
    this->board.Init(2, 4, bgSprite->GetWidthS(), bgSprite->GetHeightS());

    // Cria o timer
    std::shared_ptr<GameObject> timerGO = std::make_shared<GameObject>();
    std::shared_ptr<TurnTimer> turnTimer = std::make_shared<TurnTimer>(timerGO);

    timerGO->AddComponent(turnTimer);
    this->AddObject(timerGO);

    // Cria sprite para representar baralho de eventos
    std::shared_ptr<GameObject> eventGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> eventSprite = std::make_shared<Sprite>(eventGO, std::string(EVENT_PATH "Back.png"));
    eventSprite->SetScale(Game::heightS / 2 / eventSprite->GetHeightS(),
     Game::heightS / 2 / eventSprite->GetHeightS());
    eventGO->AddComponent(eventSprite);
    eventGO->box.leftUp = {
        Game::widthS - eventSprite->GetWidthS() * 1.1f,
        Game::heightS - eventSprite->GetHeightS() * 1.1f
    };
    this->AddObject(eventGO);

    // Toca musica de batalha.
    this->music.Open(AUDIO_PATH "battle.ogg");
    this->music.Play(-1);
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    // Verificar se o usuário deseja fechar o jogo
    this->quitRequested |= input.QuitRequested() || input.IsKeyPress(ESCAPE_KEY);
    GameData::quitAll |= input.QuitRequested();
    if(GameData::enemyCount == 0) {
        this->quitRequested = true;
        GameData::stagesBeated++;
    }
}

void StageState::Render() {
    this->RenderArray();
}

void StageState::Start() {
    if(!this->started) {
        this->LoadAssets();
    }
    this->StartArray();
    this->started = true;
}

int StageState::AddCard(std::string file, int num) {
    std::shared_ptr<GameObject> playerCard = std::make_shared<GameObject>();
    std::shared_ptr<Card> card = std::make_shared<Card>(playerCard, file, num);
    playerCard->AddComponent(card);

    this->AddObject(playerCard);
    return this->board.AddCard(card);
}

void StageState::Pause() {
    this->music.Stop();
}

void StageState::Resume() {
    this->music.Play(-1);
}