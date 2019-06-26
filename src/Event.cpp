#include "Event.h"
#include "Common.h"
#include "Action.h"
#include "Board.h"
#include "Common.h"  // para realizacao do sorteio de evento

bool Event::occured = false;
void Event::Meteor(int qtd, int damage) {
    if(damage < 0) {
        damage = randInt(1, 4);
    }
    for(int i = 0; i < qtd; i++) {
        Action::AnonymousAttack(damage, randInt(-2, 2));
    }
}

void Event::Run() {
  int whichEvent = randInt(0, 1);
  printf("evento : %d\n", whichEvent);
  switch (whichEvent) {
  case 1:
      Event::Meteor(randInt(0, 2), randInt(0, 3));
      break;
  default:
      break;
  }
}