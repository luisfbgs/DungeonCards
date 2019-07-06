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

TurnTimer::TurnTimer(std::shared_ptr<GameObject> associated) : Component(associated) {
    this->timerGO = std::make_shared<GameObject>();
    this->timerSprite = std::make_shared<Sprite>(this->timerGO);
    this->pointerGO = std::make_shared<GameObject>();
    this->pointerSprite = std::make_shared<Sprite>(this->pointerGO);

    TurnState::Init();
    printf("\nInit\n");
    printf("%s\n", turnName[TurnState::current].c_str());
    TurnState::turnEnded = false;
    this->timerSprite->Open(TIMER_PATH + std::string("timert.png"));
    float scale = (Game::heightS / 2.0) / this->timerSprite->GetHeight();
    this->timerSprite->SetScale(scale, scale);
    this->pointerSprite->Open(TIMER_PATH + std::string("pointer.png"));
    this->pointerSprite->SetScale(scale, scale);
    this->pointerGO->box.leftUp = {this->timerSprite->GetWidthS() / 2.235f, this->timerSprite->GetHeightS() / 3.29f};
}

void TurnTimer::Update(int dt) {
    this->timer.Update(dt);
    if(this->timer.Get() >= this->kTurnLength) {
        if(GameData::runningAnimations) {
            TurnState::turnEnded = true;
            return;
        }
        TurnState::turnEnded = false;
        this->timer.Restart();
        TurnState::Next();
        printf("%s\n", turnName[TurnState::current].c_str());
    }

    float clockNum = 360.0f * this->timer.Get() / this->kTurnLength;
    this->pointerSprite->SetAngle(clockNum);
}

void TurnTimer::Render() {
    this->timerSprite->Render();
    this->pointerSprite->Render();
    TurnState::Render();
}

bool TurnTimer::Is(const std::string &type) {
    return type == "TurnTimer";
}