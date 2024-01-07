//
// Created by je_gi on 2023-11-16.
//
#include "../headers/Board.hpp"

[[maybe_unused]] BoardTile& Board::getTile(int boardPosition) {
    return *this->tiles[boardPosition % 40];
}

[[maybe_unused]] void Board::AddTile(BoardTile *boardTilePtr) {
    this->tiles.push_back(boardTilePtr);
}

[[maybe_unused]] int Board::getTileCount() const {
    return (int)this->tiles.size();
}