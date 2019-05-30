#include <memory>
#include <string>

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

StageState::StageState() : board(Board::GetInstance()) {}

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
    Camera::pos = {blackBarX / 2, blackBarY / 2};

    this->AddObject(bgGO);

    // Criar tabuleiro
    this->board.Init(2, 4);

    // Cria uma carta
    this->AddCard(std::string("assets/img/player.jpeg"));
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    this->quitRequested = input.IsKeyDown(ESCAPE_KEY);
    // Verificar se o usuário deseja fechar o jogo
    GameData::quitAll = input.QuitRequested();
    
    // Mover a carta 0
    int yMove = input.KeyPress('s') - input.KeyPress('w');
    int xMove = input.KeyPress('d') - input.KeyPress('a');
    if(xMove || yMove) {
        Action::Move(this->board.GetCard(0).get(), {xMove, yMove}, this->board.GetBoardPos(0));
    }
}

void StageState::Render() {
    this->RenderArray();
}

void StageState::Start() {
    this->LoadAssets();
    this->StartArray();
}

int StageState::AddCard(std::string file) {
    GameObject *playerCard = new GameObject();
    std::shared_ptr<Card> card(new Card(*playerCard, file));
    playerCard->AddComponent(card);

    this->AddObject(playerCard);
    return this->board.AddCard(card);
}

void StageState::Pause() {
}

void StageState::Resume() {
}