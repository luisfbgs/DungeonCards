#include "CardSkill.h"
#include "Card.h"
#include "Board.h"

/// Retorna a nova vida do inimigo apos tê-lo healado.
int CardSkill::HealCard(Card* target, int hp) {
    return target->_Heal(hp);
}

int CardSkill::DoubleDamage(Card* target, Card* self) {
  return target->_Damage( self->GetAttackPower() );
}

int CardSkill::Immolate(Card* target, Card* self) {
  return target->_Damage(9 - self->hp);
}

int CardSkill::FireWall(Card* target, Card* self) {
  return target->_Damage(1);
}

void CardSkill::WolfSpirit(Card* target) {
  target->myAttibutes |= Card::Attributes::doubleDamage;
}

bool CardSkill::IsPassive(int id) {
  (void) id;
  return false;
}

bool CardSkill::Run(int id, Vec2Int pos, Card* source, std::weak_ptr<Card> lastTarget) {
  auto target = Board::GetInstance().GetCard(pos);
  auto targetLeft = Board::GetInstance().GetCard({pos.x-1, pos.y});
  auto targetRight = Board::GetInstance().GetCard({pos.x+1, pos.y});
  switch (id) {
  case 1:
    if(target != nullptr && !target->isDead) {
      CardSkill::Immolate(target.get(), source);
      return true;
    }
    break;
  case 2:
    if(target != nullptr && !target->isDead) {
      CardSkill::FireWall(target.get(), source);
    }

    if(targetLeft != nullptr && !targetLeft->isDead) {
      CardSkill::FireWall(targetLeft.get(), source);
    }

    if(targetRight != nullptr && !targetRight->isDead) {
      CardSkill::FireWall(targetRight.get(), source);
    }
    return target || targetLeft || targetRight;
    break;
  case 3:
    if(target != nullptr && !target->isDead) {
      CardSkill::HealCard(target.get());
      return true;
    }
    break;
  case 4:
    if(target != nullptr && !target->isDead) {
      CardSkill::WolfSpirit(target.get());
      return true;
    }
    break;
  }
  return false;
}