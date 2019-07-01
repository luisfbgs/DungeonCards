#include <string>
#include <memory>

#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "PlayerHand.h"

Player::Player(std::shared_ptr<GameObject> associated, const std::string &cardFile, int num) : Component(associated) {
    std::shared_ptr<GameObject> cardGO(new GameObject());
    this->cardFile = cardFile;
    this->card = std::shared_ptr<Card>(new Card(cardGO, cardFile, num));
    cardGO->AddComponent(this->card);
    Board::GetInstance().AddCard(this->card);

    std::shared_ptr<GameObject> playerHandGO(new GameObject());
    this->playerHand = std::shared_ptr<PlayerHand>(new PlayerHand(playerHandGO, CURSOR_PATH + std::to_string(num) + ".png", num));
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