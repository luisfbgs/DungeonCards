#include <string>
#include <memory>

#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "PlayerHand.h"

Player::Player(std::shared_ptr<GameObject> associated, const std::string &cardFile, int num) : Component(associated) {
    std::shared_ptr<GameObject> cardGO = std::make_shared<GameObject>();
    this->cardFile = cardFile;
    this->card = std::make_shared<Card>(cardGO, cardFile, num);
    cardGO->AddComponent(this->card);
    Board::GetInstance().AddCard(this->card);

    std::shared_ptr<GameObject> playerHandGO = std::make_shared<GameObject>();
    this->playerHand = std::make_shared<PlayerHand>(playerHandGO, CURSOR_PATH + std::to_string(num) + ".png", num);
    playerHandGO->AddComponent(this->playerHand);
}

void Player::Update(int dt) {
    this->card->Update(dt);
}

void Player::Render() {
    this->card->Render();
}

bool Player::Is(const std::string &type) {
    return type == "Player";
}