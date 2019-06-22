#pragma once

enum Turn{
    PlayerAttack,
    EnemyAttack,
    Event,
    PlayerSkill
};
class TurnState {
public:
    static Turn current;
    static void Init();
    static void Next();
};