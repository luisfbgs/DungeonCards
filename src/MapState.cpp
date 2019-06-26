#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "MapState.h"
#include "StageState.h"
#include "InputManager.h"

void MapState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "map.png"));
    float bgScale = std::min((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);
}

void MapState::Start() {
    this->pos = 1;
    this->LoadAssets();
}

void MapState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress(' ')) {
        Game::GetInstance().Push(new StageState());
    }
    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
}

void MapState::Render(){
    this->RenderArray();
}

void MapState::Pause(){
}

void MapState::Resume(){
}