#ifndef BOARD
#define BOARD

#include <vector>
#include <memory>
#include "Card.h"

class Board {
public:
    void Init(int rows, int columns);
    int AddCard(std::shared_ptr<Card> card);
    void MoveCard(int id, int posx, int posy);
private:
    float cellW, cellH;
    int rows, columns;
    std::vector<std::shared_ptr<Card>> cards;
};

#endif