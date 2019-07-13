#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CongratsState.h"
#include "Stages.h"
#include "InputManager.h"
#include "Sound.h"
#include <iostream>

CongratsState::CongratsState(State* caller) {
    this->caller = caller;
}

CongratsState::CongratsState() {
    this->caller = nullptr;
}

CongratsState::~CongratsState() {
    if (this->caller) {
        this->caller->quitRequested = true;
    }
}

void CongratsState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(
        bgGO, STAGE_PATH "Congrats.png"
    );
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

}

void CongratsState::Start() {
    this->LoadAssets();

    // Toca musica de batalha.
    this->music.Open(AUDIO_PATH "endStateWin.ogg");
    this->music.Play(-1);
}

void CongratsState::Update(int dt) {
    (void)dt;
    static InputManager& instance = InputManager::GetInstance();

    this->quitRequested |= instance.QuitRequested() || instance.IsKeyPress(ESCAPE_KEY);
    GameData::quitAll |= instance.QuitRequested();
}

void CongratsState::Render(){
    this->RenderArray();
}

void CongratsState::Pause(){
}

void CongratsState::Resume(){
}

