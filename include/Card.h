#ifndef CARD
#define CARD

#include <string>
#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Card : public Component {
public:
    Card(GameObject &associated, std::string file, int hp = 10);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void Move(int posX, int posY);
    void SetScale(float cellW, float cellH);
private:
    int hp;
    int szW, szH;
    int posX, posY;
    Sprite sprite;
};

#endif