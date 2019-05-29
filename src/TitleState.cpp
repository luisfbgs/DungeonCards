#include "TitleState.h"
#include "StageState.h"
#include "Game.h"

void TitleState::Update(int dt) {
    (void)dt;
    Game::GetInstance().Push(new StageState());
}

void TitleState::LoadAssets() {
}

void TitleState::Render() {
}

void TitleState::Start() {
    this->LoadAssets();
    this->UpdateArray(0);
}

void TitleState::Pause() {}

void TitleState::Resume() {
}