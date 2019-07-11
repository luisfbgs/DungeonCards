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

    this->turnArtSpriteGO = std::shared_ptr<GameObject>(new GameObject);
    this->turnArtSprite = std::make_shared<Sprite>(this->turnArtSpriteGO);

}

TurnState::~TurnState() {
    instance = nullptr;
}

void TurnState::Init() {
    static TurnState instance;
    TurnState::instance = &instance;
    TurnState::current = Turn::PlayerAttack;
    auto umCentoWidth = (float)(Game::GetInstance().widthS) / 100.0f;
    auto umCentoHeight = (float)(Game::GetInstance().heightS) / 100.0f;
    instance.turnSprite->Open(TURN_PATH + turnName[TurnState::current] + ".png");
    instance.turnArtSprite->Open(TURN_PATH "art_" + turnName[TurnState::current] + ".png");
    instance.SetScale();
    instance.turnArtSpriteGO->box.leftUp = {
        3 * umCentoWidth,
        65 * umCentoHeight
    };
    instance.turnSpriteGO->box.CenterIn({
        (Game::GetInstance().widthS/2.0f),
        (Game::GetInstance().heightS/2.0f) + (Game::GetInstance().heightS / 10)*0.65
    });
    // .leftUp = {-100, instance.turnSprite->GetHeightS()};
}

void TurnState::SetScale() {
    float scaleSprite = (Game::heightS / 2.0f) / this->turnSprite->GetHeight();
    this->turnSprite->SetScale(scaleSprite, scaleSprite);

    float scaleArtSprite = (Game::heightS / 3.5f) / this->turnArtSprite->GetHeightS();
    this->turnArtSprite->SetScale(scaleArtSprite, scaleArtSprite);
}

void TurnState::Next() {
    TurnState::current = Turn((TurnState::current + 1) % TURN);
    TurnState::instance->turnSprite->Open(TURN_PATH + turnName[TurnState::current] + ".png");
    TurnState::instance->turnArtSprite->Open(TURN_PATH "art_" + turnName[TurnState::current] + ".png");
}

void TurnState::Render() {
    TurnState::instance->turnSprite->Render();
    TurnState::instance->turnArtSprite->Render();
}