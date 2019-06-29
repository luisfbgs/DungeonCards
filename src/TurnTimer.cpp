#include <string>
#include <cstdio>
#include <chrono>
#include <thread>

#include "TurnTimer.h"
#include "Component.h"
#include "Timer.h"
#include "GameData.h"
#include "Game.h"
#include "TurnState.h"

TurnTimer::TurnTimer(GameObject &associated) : Component(associated), timerSprite(associated) {
    TurnState::Init();
    printf("\nInit\n");
    printf("%s\n", turnName[TurnState::current].c_str());
}

void TurnTimer::SetScale() {
    float scale = (Game::heightS / 2.0) / this->timerSprite.GetHeight();
    this->timerSprite.SetScale(scale, scale);
}

void TurnTimer::Update(int dt) {
    this->timer.Update(dt);
    if(this->timer.Get() >= this->kTurnLength) {
        if(GameData::runningAnimations) {
            return;
        }
        this->timer.Restart();
        TurnState::Next();
        printf("%s\n", turnName[TurnState::current].c_str());
    }

    int clockNum = this->timer.Get()  / (this->kTurnLength / 12.0);
    clockNum++;
    this->timerSprite.Open(std::string("assets/img/Timer") + std::to_string(clockNum) + ".png");
    this->SetScale();
}

void TurnTimer::Render() {
    this->timerSprite.Render();
    TurnState::Render();
}

bool TurnTimer::Is(const std::string &type) {
    return type == "TurnTimer";
}