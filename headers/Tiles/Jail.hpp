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
    ~Jail() override = default;
    void onVisit(Player *plyr) override {
        std::cout<<"Free park at jail by player " << plyr->getName() << '\n';
    }
    [[maybe_unused]] std::pair<sf::Vector2f, uint8_t> addPlayerToJail(Player *playerptr); /// returns the position coordinates and index
    [[maybe_unused]] void removePlayerFromJail(uint8_t positionInsideTile);
    [[maybe_unused]] void removePlayerFromJail(const Player *playerPtr);
};

#endif //OOP_JAILTILE_HPP
