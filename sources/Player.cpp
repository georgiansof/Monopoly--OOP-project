#include "../headers/Player.hpp"

using namespace std;
using namespace sf;

pair<uint16_t,bool> Player::incrementPosition(int amount) noexcept {
    this->boardPosition += amount;
    bool start = false;
    if(this->boardPosition >= BOARD_TILES_NUMBER) {
        this->boardPosition %= BOARD_TILES_NUMBER;
        start = true;
    }
    return {boardPosition,start};
}

uint16_t Player::getBoardPosition() const noexcept {
    return this->boardPosition;
}

uint8_t Player::getIndexInsideTile() const noexcept {
    return this->indexInsideTile;
}

uint16_t Player::operator++(int) noexcept {return this->incrementPosition().first;}
uint16_t Player::operator++() noexcept {return this->incrementPosition().first;}

PlayerEconomy::PlayerEconomy(uint32_t money) {
    this -> money = money;
}

Color Player::getColor() const noexcept {
    return this->color;
}

[[nodiscard]] const std::string & Player::getName() const noexcept {
    return this->name;
}

Player::Player(const Player& other) : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = new sf::CircleShape(*other.boardPieceShapePtr);
}


Player::Player(Player&& other) noexcept : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = other.boardPieceShapePtr;

    other.boardPosition = -1;
    other.name = "";
    other.color = sf::Color::Transparent;
    other.indexInsideTile = -1;
    other.boardPieceShapePtr = nullptr;
}

Player& Player::operator=(const Player& other) {
    if(&other != this) {
        this->money = other.money;
        this->boardPosition = other.boardPosition;
        this->name = other.name;
        this->color = other.color;
        this->indexInsideTile = other.indexInsideTile;
        this->boardPieceShapePtr = new sf::CircleShape(*other.boardPieceShapePtr);
    }
    return *this;
}

Player& Player::operator=(Player&& other) noexcept {
    if(&other != this) {
        this->boardPosition = other.boardPosition;
        this->name = other.name;
        this->color = other.color;
        this->indexInsideTile = other.indexInsideTile;
        this->boardPieceShapePtr = other.boardPieceShapePtr;

        other.boardPosition = -1;
        other.name = "";
        other.color = sf::Color::Transparent;
        other.indexInsideTile = -1;
        other.boardPieceShapePtr = nullptr;
    }
    return *this;
}

Player::~Player() {
    delete this->boardPieceShapePtr;
    this->boardPieceShapePtr = nullptr;
}