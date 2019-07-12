#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "GameOverState.h"
#include "Stages.h"
#include "InputManager.h"
#include "Sound.h"
#include <iostream>
using std::cout;
using std::endl;

GameOverState::GameOverState(State* caller) {
    this->caller = caller;
}

GameOverState::GameOverState() {
    this->caller = nullptr;
}

GameOverState::~GameOverState() {
    if (this->caller) {
        this->caller->quitRequested = true;
    }
    Game::GetInstance().GetCurrentState().quitRequested = true;
}

void GameOverState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(
        bgGO, STAGE_PATH "GameOver.png"
    );
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

}

void GameOverState::Start() {
    this->LoadAssets();
}

void GameOverState::Update(int dt) {
    (void)dt;
    static InputManager& instance = InputManager::GetInstance();

    this->quitRequested |= instance.QuitRequested() || instance.IsKeyPress(ESCAPE_KEY);
    GameData::quitAll |= instance.QuitRequested();
}

void GameOverState::Render(){
    this->RenderArray();
}

void GameOverState::Pause(){
}

void GameOverState::Resume(){
}

