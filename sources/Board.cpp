//
// Created by je_gi on 2023-11-16.
//
#include "../headers/Board.hpp"

BoardTile& Board::getTile(int boardPosition) {
    return *this->tiles[boardPosition % 40];
}

void Board::AddTile(BoardTile *boardTilePtr) {
    this->tiles.push_back(boardTilePtr);
}

int Board::getTileCount() const {
    return (int)this->tiles.size();
}