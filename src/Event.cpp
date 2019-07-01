#include <vector>

#include "Event.h"
#include "Animation.h"
#include "Game.h"
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
    if(targets.size()) {
        Card* target = targets[randInt(0, targets.size() - 1)];
        Action::AnonymousHeal(3, target->playerNum);

    }
}

void Event::PlayersRest() {
    std::vector<Card*> targets;
    GameData::AddAlivePlayers(targets);
    for(auto target : targets) {
        Action::AnonymousHeal(1, target->playerNum);
    }
}

void Event::Immune() {
    
}

void Event::Volunteer() {
    
}

void Event::Run() {
    int whichEvent = randInt(0, 2);
    // Adiciona animação de escolha de evento
    std::shared_ptr<GameObject> eventAniGO(new GameObject());
    std::shared_ptr<EventAnimation> eventAni(new EventAnimation(eventAniGO, whichEvent));
    eventAniGO->AddComponent(eventAni);
    Game::GetInstance().GetCurrentState().AddObject(eventAniGO);
}

void Event::ChooseEvent(int whichEvent) {
    switch (whichEvent) {
        case METEOR:
            Event::Meteor(randInt(1, 2), randInt(1, 3));
            break;
        case REST:
            Event::Rest();
            break;
        case PLAYERS_REST:
            Event::PlayersRest();
            break;
        default:
            break;
    }
}