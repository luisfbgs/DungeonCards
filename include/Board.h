#ifndef BOARD
#define BOARD

#include <vector>
#include <memory>
#include <map>
#include "Card.h"
#include "Vec2Int.h"
#include "Action.h"

class Board {
public:
    Board();
    void Init(int rows, int columns);
    int AddCard(std::shared_ptr<Card> card);
    void MoveCard(int id, Vec2Int pos, Vec2Int offset = {0, 0});
    Vec2Int GetBoardPos(int id);
    std::shared_ptr<Card> GetCard(int id);
    float GetCellW();
    float GetCellH();
    static Board& GetInstance();
    void InitActionMap();
private:
    float cellW, cellH;
    int rows, columns;
    std::vector<std::shared_ptr<Card>> cards;
};

#endif