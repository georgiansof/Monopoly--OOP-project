//
// Created by je_gi on 2023-11-16.
//

#ifndef OOP_JAILTILE_HPP
#define OOP_JAILTILE_HPP

#include <vector>
#include "BoardTile.hpp"
#include "Player.hpp"

class Jail : public BoardTile {
    sf::Vector2f playerPositionsImprisoned[9];
    std::vector<Player*> playersImprisoned;
public:
    Jail();
    ~Jail() = default;
};

#endif //OOP_JAILTILE_HPP
