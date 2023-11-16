//
// Created by je_gi on 2023-11-04.
//

#ifndef OOP_PLAYER_HPP
#define OOP_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>
#include "../constants.hpp"

class Game;

struct PlayerEconomy {
protected:
    uint32_t money;
    explicit PlayerEconomy(uint32_t money = PLAYER_START_MONEY);
    friend Game;
};

class Player : public PlayerEconomy {
    std::string name;
    sf::Color color;
    uint16_t boardPosition;
    uint8_t indexInsideTile;
public:
    Player(std::string name, sf::Color color, uint32_t money = PLAYER_START_MONEY) : PlayerEconomy(money), name(std::move(name)), color(color) {boardPosition = 0;}
    Player(const char* name, sf::Color color, uint32_t money = PLAYER_START_MONEY) : PlayerEconomy(money), name(name), color(color) {boardPosition = 0;}
    Player() = delete;
    int incrementPosition() noexcept;
    uint16_t operator++(int) noexcept;
    uint16_t operator++() noexcept;
    [[nodiscard]] sf::Color getColor() const noexcept;
    [[nodiscard]] const std::string & getName() const noexcept;
    void setIndexInsideTile(uint8_t index);
};

#endif //OOP_PLAYER_HPP
