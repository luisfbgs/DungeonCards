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
#include "Sound.h"

TurnTimer::TurnTimer(std::shared_ptr<GameObject> associated) : Component(associated) {
    this->timerGO = std::make_shared<GameObject>();
    this->timerSprite = std::make_shared<Sprite>(this->timerGO);
    this->timerGO->box.leftUp = {
        ((float)(Game::GetInstance().widthS) / 1000) * 0,
        ((float)(Game::GetInstance().heightS) / 100) * 0
    };
    this->pointerGO = std::make_shared<GameObject>();
    this->pointerSprite = std::make_shared<Sprite>(this->pointerGO);
    float reductionFactor = 1.5;

    TurnState::Init();
    TurnState::turnEnded = false;
    this->timerSprite->Open(TIMER_PATH + std::string("timert.png"));
    float scale = ( (Game::heightS / 2.0) / this->timerSprite->GetHeight() ) * reductionFactor;
    this->timerSprite->SetScale(scale, scale);
    this->pointerSprite->Open(TIMER_PATH + std::string("pointer.png"));
    this->pointerSprite->SetScale(scale, scale);
    this->pointerGO->box.leftUp = this->timerGO->box.leftUp +
        Vec2(this->pointerSprite->GetWidthS() * 4.525, this->pointerSprite->GetHeightS() * 0.76);
}

void TurnTimer::Update(int dt) {
    this->timer.Update(dt);
    if(this->timer.Get() >= this->kTurnLength) {
        if(GameData::runningAnimations) {
            TurnState::turnEnded = true;
            return;
        }
        Sound::PlaySound("troca_de_turno.wav");
        TurnState::turnEnded = false;
        this->timer.Restart();
        TurnState::Next();
        if(TurnState::current == PlayerSkill) {
            for(auto card : GameData::players) {
                if(!card.expired()) {
                    card.lock()->card->myAttibutes = Card::Attributes::clear;
                }
            }
            for(auto card : GameData::enemies) {
                if(!card.expired()) {
                    card.lock()->myAttibutes = Card::Attributes::clear;
                }
            }
        }
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