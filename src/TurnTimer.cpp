#include <string>
#include <cstdio>

#include "TurnTimer.h"
#include "Component.h"
#include "Timer.h"
#include "GameData.h"
#include "Game.h"
#include "TurnState.h"

TurnTimer::TurnTimer(GameObject &associated) : Component(associated), timerSprite(associated) {
    TurnState::Init();
}

void TurnTimer::SetScale() {
    float scale = (Game::GetInstance().GetWidth() / 7.0) / this->timerSprite.GetWidth();
    this->timerSprite.SetScale(scale, scale);
    this->baseScale = scale;
}

void TurnTimer::Update(int dt) {
    if(TurnState::current == EnemyAttack) {
        this->timer.Restart();
        TurnState::Next();
        return;
    }
    this->timer.Update(dt);
    if(this->timer.Get() >= this->kTurnLength) {
        this->SetScale();
        this->timer.Restart();
        TurnState::Next();
    }

    int clockNum = this->timer.Get()  / (this->kTurnLength / 12.0);
    clockNum++;
    this->timerSprite.Open(std::string("assets/img/Timer") + std::to_string(clockNum) + ".png");
    this->SetScale();
}

void TurnTimer::Render() {
    this->timerSprite.Render();
}

bool TurnTimer::Is(const std::string &type) {
    return type == "TurnTimer";
}