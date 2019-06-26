#pragma once
#include "Card.h"

class CardSkill {
private:
  CardSkill();
public:
  static int HealCard(Card* target, int hp = 2);
  static int DoubleDamage(Card* target, Card* self);
};