#include "TitleState.h"

void TitleState::Update(int dt) {
    (void)dt;
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