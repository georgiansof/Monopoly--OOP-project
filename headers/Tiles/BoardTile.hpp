//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_BOARDTILE_HPP
#define OOP_BOARDTILE_HPP

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Player.hpp"

class BoardTile {
public:
    enum Type {JAIL, PROPERTY, TAX, PARK, CHANCE};
private:
    const uint16_t boardPosition;
    const BoardTile::Type type;
protected:
    sf::Vector2f playerPositions[9];
    Player* occupiedPositions[9] {};
    explicit BoardTile(uint16_t boardPosition, BoardTile::Type type);
    [[nodiscard]] uint16_t getBoardPosition() const noexcept;
public:
    std::pair<sf::Vector2f, uint8_t> addPlayer(Player *playerPtr); /// returns the position coordinates and index
    void removePlayer(uint8_t positionInsideTile);
    void removePlayer(Player *playerPtr);
    BoardTile() = delete;
    ~BoardTile() = default;

};



#endif //OOP_BOARDTILE_HPP
