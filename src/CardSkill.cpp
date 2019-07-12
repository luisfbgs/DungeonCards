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

bool CardSkill::IsPassive(int id) {
  return id == 0;
}

bool CardSkill::Run(int id, Vec2Int pos, Card* source, std::weak_ptr<Card> lastTarget) {
  switch (id) {
  case 0:
    if(!lastTarget.expired() && !lastTarget.lock()->isDead) {
      CardSkill::DoubleDamage(lastTarget.lock().get(), source);
      return true;
    }
    break;
  case 1:
    auto target = Board::GetInstance().GetCard(pos);
    if(target != nullptr && !target->isDead) {
      CardSkill::HealCard(target.get());
      return true;
    }
    break;
  }
  return false;
}