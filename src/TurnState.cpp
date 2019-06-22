#include "TurnState.h"

Turn TurnState::current;

void TurnState::Init() {
    TurnState::current = Turn::PlayerAttack;
}

void TurnState::Next() {
    TurnState::current = Turn((TurnState::current + 1) % 4);
}