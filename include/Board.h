#ifndef BOARD
#define BOARD

#include <vector>
#include <memory>
#include "Card.h"
#include "Vec2Int.h"

class Board {
public:
    void Init(int rows, int columns);
    int AddCard(std::shared_ptr<Card> card);
    void MoveCard(int id, Vec2Int pos, Vec2Int offset = {0, 0});
    Vec2Int GetBoardPos(int id);
private:
    float cellW, cellH;
    int rows, columns;
    std::vector<std::shared_ptr<Card>> cards;
};

#endif