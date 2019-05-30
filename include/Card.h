#ifndef CARD
#define CARD

#include <string>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2Int.h"
#include "Action.h"

class Board;
class Action;

class Card : public Component {
friend Board;
friend Action;
public:
    Card(GameObject &associated, std::string file, int num = 0, int hp = 100);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void SetScale();
    int GetNum();
private:
    // playerNum é positivo para jogadores e negativo para inimigos
    int playerNum;
    int hp;
    bool hasMoved;
    int szW, szH;
    Vec2Int pos;
    Sprite sprite;
    Sprite lifeBar;
    float lifeBarSize;
};

#endif