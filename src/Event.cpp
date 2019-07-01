#include <vector>

#include "Event.h"
#include "GameData.h"
#include "Common.h"
#include "Action.h"
#include "Board.h"
#include "Common.h"  // para realizacao do sorteio de evento

bool Event::occured = false;

void Event::Meteor(int qtd, int damage) {
    if(damage < 0) {
        damage = randInt(1, 4);
    }

    std::vector<Card*> targets;
    GameData::AddAliveEnemies(targets);
    GameData::AddAlivePlayers(targets);

    if(targets.size()) {
        for(int i = 0; i < qtd; i++) {
            Card* target = targets[randInt(0, targets.size() - 1)];
            Action::AnonymousAttack(damage, target->playerNum);
        }
    }
}

void Event::Rest() {
    std::vector<Card*> targets;
    GameData::AddAlivePlayers(targets);
    
}

void Event::PlayersRest() {
    
}

void Event::Immune() {
    
}

void Event::Volunteer() {
    
}

void Event::Run() {
  int whichEvent = randInt(1, 1);
  switch (whichEvent) {
  case 1:
      Event::Meteor(randInt(1, 2), randInt(1, 3));
      break;
  default:
      break;
  }
}