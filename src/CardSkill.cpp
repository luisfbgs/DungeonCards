#include "CardSkill.h"

/// Retorna a nova vida do inimigo apos tê-lo healado.
int CardSkill::HealCard(Card* target, int hp) {
  return target->_Heal(hp);
}

int CardSkill::DoubleDamage(Card* target, Card* self) {
  return target->_Damage( self->GetAttackPower() );
}