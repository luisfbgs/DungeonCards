#ifndef CARD
#define CARD

#include <string>
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2Int.h"
#include "Action.h"
#include "ActionMove.h"
class Board;

class Card : public Component {
friend Board;
friend Action;
friend ActionMove;
public:
    Card(GameObject &associated, std::string file, int hp = 10);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void Move(Vec2Int pos);
    void SetScale();
private:
    int hp;
    int szW, szH;
    Vec2Int pos;
    Sprite sprite;
};

#endif