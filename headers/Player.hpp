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

class PlayerEconomy {
protected:
    uint32_t money;
    explicit PlayerEconomy(uint32_t money = PLAYER_START_MONEY);
    PlayerEconomy(const PlayerEconomy& other) = default;
    PlayerEconomy(PlayerEconomy&& other) = default;
    friend Game;
};

class PlayerPiece {
protected:
    uint8_t indexInsideTile = -1;
    sf::CircleShape *boardPieceShapePtr = nullptr;
    PlayerPiece(sf::CircleShape *boardPieceShapePtr, uint8_t indexInsideTile)
        : indexInsideTile(indexInsideTile), boardPieceShapePtr(boardPieceShapePtr)
        {}
    friend Game;
};

class Player : public PlayerEconomy, public PlayerPiece {
    std::string name;
    sf::Color color;
    uint16_t boardPosition;
public:
    Player(std::string name, sf::Color color, uint32_t money = PLAYER_START_MONEY,
           uint16_t boardPosition = 0, uint8_t indexInsideTile = 0,
           sf::CircleShape *shapePtr = nullptr)
                : PlayerEconomy(money),
                   PlayerPiece(shapePtr, indexInsideTile),
                   name(std::move(name)), color(color), boardPosition(boardPosition)
                   {}
    Player(const char* name, sf::Color color, uint32_t money = PLAYER_START_MONEY,
           uint16_t boardPosition = 0, uint8_t indexInsideTile = 0,
           sf::CircleShape *shapePtr = nullptr)
                : PlayerEconomy(money),
                   PlayerPiece(shapePtr, indexInsideTile),
                   name(name), color(color), boardPosition(boardPosition)
                   {}
    Player() = delete;

    Player(const Player& other);
    Player(Player&& other) noexcept;

    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;

    ~Player();

    uint16_t operator++(int) noexcept;
    uint16_t operator++() noexcept;

    [[nodiscard]] sf::Color getColor() const noexcept;
    [[nodiscard]] const std::string & getName() const noexcept;
    [[nodiscard]] uint16_t getBoardPosition() const noexcept;
    [[nodiscard]] uint8_t getIndexInsideTile() const noexcept;


    std::pair<uint16_t,bool> incrementPosition(int amount = 1) noexcept;
};

#endif //OOP_PLAYER_HPP
