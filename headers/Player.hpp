//
// Created by je_gi on 2023-11-04.
//

#ifndef OOP_PLAYER_HPP
#define OOP_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>
#include "../constants.hpp"

class Player {
    std::string name;
    sf::Color color;
    uint16_t boardPosition;
public:
    Player(std::string name, sf::Color color) : name(std::move(name)), color(color) {boardPosition = 0;}
    Player() = delete;
    int incrementPosition() noexcept;
    uint16_t operator++(int) noexcept;
    uint16_t operator++() noexcept;
};

#endif //OOP_PLAYER_HPP
