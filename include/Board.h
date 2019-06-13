#pragma once

#include <vector>
#include <memory>
#include <map>
#include "Card.h"
#include "Vec2Int.h"
#include "Action.h"

class Board {
public:
    void Init(int rows, int columns, float sizeW, float sizeH);
    int AddCard(std::shared_ptr<Card> card);
    void MoveCard(int id, Vec2Int pos, Vec2Int offset = {0, 0});
    Vec2Int GetBoardPos(int id);
    std::shared_ptr<Card> GetCard(int id);
    std::shared_ptr<Card> GetCard(int x, int y);
    std::shared_ptr<Card> GetCard(Vec2Int vec);
    float GetCellW();
    float GetCellH();
    int GetRows();
    int GetColumns();
    static Board& GetInstance();
    void InitActionMap();
    void Reset();
private:
    float cellW, cellH;
    int rows, columns;
    std::map<int, std::weak_ptr<Card>> cards;
};
