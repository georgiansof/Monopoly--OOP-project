//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_PARKTILE_HPP
#define OOP_PARKTILE_HPP

#include "BoardTile.hpp"

class ParkTile : protected BoardTile {
public:
    enum Type {START, JAIL_VISIT, FREE_PARKING, GO_TO_JAIL};
private:
    ParkTile::Type type;
public:
    ParkTile(unsigned short boardPosition, ParkTile::Type type)
    : BoardTile(boardPosition, PARK), type(type) {}
    ParkTile() = delete;
    ~ParkTile() = default;
};

#endif //OOP_PARKTILE_HPP
