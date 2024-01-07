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
class BoardTile;
class Property;

class PlayerEconomy {
protected:
    volatile uint32_t money;
    explicit PlayerEconomy(uint32_t money = PLAYER_START_MONEY);
    PlayerEconomy(const PlayerEconomy& other) = default;
    PlayerEconomy(PlayerEconomy&& other) = default;
    friend Game;
public:
    [[nodiscard]] uint32_t getAvailableMoney() const noexcept;
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
    std::string colorName;

    bool inJail = false;
    int timesRolledInJail = 0;


    std::vector<Property*> ownedProperties;

    void setColorName(sf::Color color);
    std::pair<uint16_t,bool> incrementPosition(int amount = 1) noexcept;

    static volatile bool buyOrPassPressed;
    static volatile bool buying;

    static void buyButtonAction();
    static void passButtonAction();
public:
    static void setBuyOrPassPressed(bool val);
    static void setBuying(bool val);

    Player(std::string name, sf::Color color, uint32_t money = PLAYER_START_MONEY,
           uint16_t boardPosition = 0, uint8_t indexInsideTile = 0,
           sf::CircleShape *shapePtr = nullptr)
                : PlayerEconomy(money),
                   PlayerPiece(shapePtr, indexInsideTile),
                   name(std::move(name)), color(color), boardPosition(boardPosition)
                   {setColorName(color);}
    Player(const char* name, sf::Color color, uint32_t money = PLAYER_START_MONEY,
           uint16_t boardPosition = 0, uint8_t indexInsideTile = 0,
           sf::CircleShape *shapePtr = nullptr)
                : PlayerEconomy(money),
                   PlayerPiece(shapePtr, indexInsideTile),
                   name(name), color(color), boardPosition(boardPosition)
                   {setColorName(color);}
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
    [[nodiscard]] bool isInJail() const noexcept;


    void sendToJail();
    void moveSpaces(int amount);
    void incrementTimesRolledInJail();

    [[nodiscard]] const std::string& getColorName() const noexcept;
    [[nodiscard]] int getTimesRolledInJail() const noexcept;

    void addOwnedProperty(Property* prop);
    void waitToPay(Player* toWho, uint32_t amount);
    void payToBank(uint32_t amount);
    bool payTo(Player *toWho, uint32_t amount);

    bool promptVisitorBuy(Property *prop);

    template<class T>
    std::vector<T*> getTilesOwnedOfType() {
        std::vector<T*> v;
        for(auto prop : ownedProperties) {
            auto *dc = dynamic_cast<T*> (prop);
            if(dc)
                v.push_back(dc);
        }
        return v;
    }
};

#endif //OOP_PLAYER_HPP
