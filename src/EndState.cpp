#include "EndState.h"

EndState::EndState() {
}


EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Update(int dt) {
    (void)dt;
    this->UpdateArray(dt);
}

void EndState::Render() {
    this->RenderArray();
}

void EndState::Start() {
}

void EndState::Pause() {}

void EndState::Resume() {}