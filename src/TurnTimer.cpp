#include <string>
#include <cstdio>

#include "TurnTimer.h"
#include "Component.h"
#include "Timer.h"
#include "GameData.h"
#include "Game.h"

TurnTimer::TurnTimer(GameObject &associated, std::string file) : Component(associated), timerSprite(associated, file) {
    this->ResetScale();
}

void TurnTimer::ResetScale() {
    float scale = (Game::GetInstance().GetWidth() / 5.0) / this->timerSprite.GetWidth();
    this->timerSprite.SetScale(scale, scale);
    this->baseScale = scale;
}

void TurnTimer::Update(int dt) {
    if(GameData::turn) {
        this->timer.Restart();
        GameData::turn ^= 1;
        return;
    }
    this->timer.Update(dt);
    if(this->timer.Get() >= 3000) {
        this->ResetScale();
        this->timer.Update(-3000);
        GameData::turn ^= 1;
    }
    float scale = this->timerSprite.GetScale().x - dt * this->baseScale / 3000;
    this->timerSprite.SetScale(scale, scale);
}

void TurnTimer::Render() {
    this->timerSprite.Render();
}

bool TurnTimer::Is(const std::string &type) {
    return type == "TurnTimer";
}