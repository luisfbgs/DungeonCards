#include <memory>
#include <string>
#include "StageState.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameData.h"
#include "Game.h"
#include <stdio.h>

void StageState::LoadAssets() {
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string("assets/img/map.png")));
    bgSprite->SetScale((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgGO->AddComponent(bgSprite);
    
    this->AddObject(bgGO);
}

void StageState::Update(int dt) {
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.IsKeyDown(ESCAPE_KEY);
    GameData::quitAll = input.QuitRequested();
}

void StageState::Render() {
    this->RenderArray();
}

void StageState::Start() {
    this->LoadAssets();
    this->StartArray();
}

void StageState::Pause() {
}

void StageState::Resume() {
}