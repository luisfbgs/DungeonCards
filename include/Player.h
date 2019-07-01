#pragma once

#include <string>
#include <memory>

#include "GameObject.h"
#include "Component.h"
#include "Card.h"
#include "PlayerHand.h"

class Player : public Component{
public:
    Player(std::shared_ptr<GameObject> associated, const std::string &cardFile, int num);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    std::shared_ptr<Card> card;
    std::shared_ptr<PlayerHand> playerHand;
    std::string cardFile;
    int playerNum;
};