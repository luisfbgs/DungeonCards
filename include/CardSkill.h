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
  static int Immolate(Card* target, Card* self);
  static int FireWall(Card* target);
  static void WolfSpirit(Card* target);
  static void Revive(Card* target);
  static bool IsPassive(int id);
  static bool Run(int id, Vec2Int pos, Card* source);
};