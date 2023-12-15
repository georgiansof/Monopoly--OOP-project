//
// Created by je_gi on 2023-11-16.
//

#ifndef OOP_JAILTILE_HPP
#define OOP_JAILTILE_HPP

#include <vector>
#include "BoardTile.hpp"
#include "../Player.hpp"

class Jail : public BoardTile {
    sf::Vector2f playerPositionsImprisoned[9];
    Player* occupiedPositionsImprisoned[9] {};
public:
    Jail();
    ~Jail() = default;
    std::pair<sf::Vector2f, uint8_t> addPlayerToJail(Player *playerptr); /// returns the position coordinates and index
    void removePlayerFromJail(uint8_t positionInsideTile);
    void removePlayerFromJail(Player *playerPtr);
};

#endif //OOP_JAILTILE_HPP
