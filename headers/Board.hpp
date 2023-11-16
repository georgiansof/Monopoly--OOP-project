//
// Created by je_gi on 2023-11-15.
//

#ifndef OOP_BOARD_HPP
#define OOP_BOARD_HPP

#include <vector>

#include "../constants.hpp"
#include "CircularList.hpp"
#include "BoardTile.hpp"

class Board {
    std::vector<BoardTile*> tiles;
public:
    BoardTile& getTile(int boardPosition);
    void AddTile(BoardTile *boardTilePtr);
    int getTileCount() const;
};

#endif //OOP_BOARD_HPP
