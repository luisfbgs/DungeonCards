#pragma once

#include <string>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2Int.h"
#include "Action.h"
#include "TurnState.h"
// #include "CardSkill.h"

class Board;
class Action;
// class CardSkill;

class Card : public Component {
friend Board;
friend Action;
// friend CardSkill;
public:
    Card(GameObject &associated, std::string file, int num = 0,
    int hp = 9, int attackPower = 3);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void SetScale();
    int GetNum();
    // '_' como prefixo pois nao eh pra ser chamado direto... em situacoes 
    // especificas. Melhorar isso.
    int _Damage(int damage);
    int _Heal(int hp);
    
    int GetAttackPower();
    Vec2Int GetPos();
    static const int MAX_LIFE = 10;
private:
    // playerNum é positivo para jogadores e negativo para inimigos
    int playerNum;
    int hp, attackPower;
    Turn lastActed;
    bool acted;
    int sizeW, sizeH;
    Vec2Int pos;
    Sprite sprite;
    Sprite lifeBar;
};