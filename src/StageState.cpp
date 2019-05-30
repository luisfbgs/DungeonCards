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

StageState::StageState() : board(Board::GetInstance()){}

void StageState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string("assets/img/board.jpeg")));
    bgSprite->SetScale((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgGO->AddComponent(bgSprite);
    
    this->AddObject(bgGO);

    // Criar tabuleiro
    this->board.Init(2, 4);

    // Criar uma carta
    this->AddCard(std::string("assets/img/player.jpeg"));
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    
    // Verificar se o usuário deseja voltar a tela inicial
    this->quitRequested = input.IsKeyDown(ESCAPE_KEY);
    // Verificar se o usuário deseja fechar o jogo
    GameData::quitAll = input.QuitRequested();
    
    // Mover a carta 0
    int yMove = input.KeyPress('s') - input.KeyPress('w');
    int xMove = input.KeyPress('d') - input.KeyPress('a');
    if(xMove || yMove) {
        ActionMove* actionMove = (ActionMove*)this->board.GetAction(ActionNames::MOVE);
        actionMove->Run( 0, {xMove, yMove}, this->board.GetBoardPos(0) );
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