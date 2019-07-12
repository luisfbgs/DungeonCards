#pragma once

#include <memory>

#include "Vec2Int.h"
#include "Card.h"

class CardSkill {
private:
  CardSkill();
public:
  static int HealCard(Card* target, int hp = 2);
  static int DoubleDamage(Card* target, Card* self);
  static bool IsPassive(int id);
  static bool Run(int id, Vec2Int pos, Card* source, std::weak_ptr<Card> lastTarget);
};