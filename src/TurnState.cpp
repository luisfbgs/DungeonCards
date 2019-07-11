#include <memory>

#include "TurnState.h"
#include "Game.h"
#include "Sprite.h"

Turn TurnState::current;
TurnState *TurnState::instance = nullptr;
bool TurnState::turnEnded = false;

TurnState::TurnState(){
    this->turnSpriteGO = std::shared_ptr<GameObject>(new GameObject);
    this->turnSprite = std::make_shared<Sprite>(this->turnSpriteGO);
}

TurnState::~TurnState() {
    instance = nullptr;
}

void TurnState::Init() {
    static TurnState instance;
    TurnState::instance = &instance;
    TurnState::current = Turn::PlayerAttack;
    instance.turnSprite->Open(TURN_PATH + turnName[TurnState::current] + ".png");
    instance.SetScale();
    instance.turnSpriteGO->box.leftUp = {-100, instance.turnSprite->GetHeightS()};
}

void TurnState::SetScale() {
    float scale = (Game::heightS / 2.0f) / this->turnSprite->GetHeight();
    this->turnSprite->SetScale(scale, scale);
}

void TurnState::Next() {
    TurnState::current = Turn((TurnState::current + 1) % TURN);
    TurnState::instance->turnSprite->Open(TURN_PATH + turnName[TurnState::current] + ".png");
}

void TurnState::Render() {
    TurnState::instance->turnSprite->Render();
}