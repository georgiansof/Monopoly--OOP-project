#include "../headers/Player.hpp"
#include "../headers/Game.hpp"

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

void Player::setColorName(sf::Color _color) {
    vector<pair<sf::Color, std::string>> colors {
            {Color::Black, "Black"},
            {Color::Yellow, "Yellow"},
            {Color::Green, "Green"},
            {Color::Red, "Red"},
            {Color::Magenta, "Magenta"},
            {Color::Blue, "Blue"},
            {Color::Cyan, "Cyan"},
            {Color::White, "White"}
    };
    for(auto &colorPair : colors)
        if(colorPair.first == _color) {
            this->colorName = colorPair.second;
            return;
        }
}

Player::Player(const Player& other) : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = new sf::CircleShape(*other.boardPieceShapePtr);
    this->colorName = other.colorName;
}


Player::Player(Player&& other) noexcept : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = other.boardPieceShapePtr;
    this->colorName = other.colorName;

    other.boardPosition = -1;
    other.name = "";
    other.color = sf::Color::Transparent;
    other.indexInsideTile = -1;
    other.boardPieceShapePtr = nullptr;
    other.colorName = "";
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

void Player::moveSpaces(int amount) {
    Game *game = Game::getInstancePtr();
    Board *board = game->getBoardPtr();
    if(!this->inJail)
        board->getTile(this->getBoardPosition()).removePlayer(this->getIndexInsideTile());
    else
        dynamic_cast<Jail&> (board->getTile(this->getBoardPosition())).removePlayerFromJail(this);
    auto updatedPosition = this->incrementPosition(amount);
    auto newPositionInsideTile = board->getTile(updatedPosition.first).addPlayer(this);
    this->indexInsideTile = newPositionInsideTile.second;
    newPositionInsideTile.first.x *= (float) game->getWindowSize().x;
    newPositionInsideTile.first.y *= (float) game->getWindowSize().y;
    this->boardPieceShapePtr->setPosition(newPositionInsideTile.first);
    if(updatedPosition.second) /// went through start
        this->money += MONEY_FROM_START;
}

void Player::sendToJail() {
    Game *game = Game::getInstancePtr();
    Board *board = game->getBoardPtr();
    if(inJail) {
        timesRolledInJail = 0;
        return;
    }
    inJail = true;
    timesRolledInJail = 0;

    board->getTile(this->getBoardPosition()).removePlayer(this);
    auto newPositionInsideTile = dynamic_cast<Jail&> (
            board->getTile(JAIL_TILE_POSITION))
                    .addPlayerToJail(this);
    newPositionInsideTile.first.x *= (float)game->getWindowSize().x;
    newPositionInsideTile.first.y *= (float)game->getWindowSize().y;
    this->boardPieceShapePtr->setPosition(newPositionInsideTile.first);
}

void Player::incrementTimesRolledInJail() {
    ++timesRolledInJail;
}

int Player::getTimesRolledInJail() const noexcept {
    return timesRolledInJail;
}

bool Player::isInJail() const noexcept {
    return this->inJail;
}

const std::string& Player::getColorName() const noexcept {
    return this->colorName;
}