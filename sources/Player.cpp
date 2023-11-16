#include "../headers/Player.hpp"

using namespace std;
using namespace sf;

int Player::incrementPosition() noexcept {
    ++this->boardPosition;
    if(boardPosition >= BOARD_TILES_NUMBER)
        boardPosition = 0; /// faster than %= BOARD_TILES_NUMBER

    return boardPosition;
}

uint16_t Player::operator++(int) noexcept {return this->incrementPosition();}
uint16_t Player::operator++() noexcept {return this->incrementPosition();}

PlayerEconomy::PlayerEconomy(uint32_t money) {
    this -> money = money;
}

Color Player::getColor() const noexcept {
    return this->color;
}

[[nodiscard]] const std::string & Player::getName() const noexcept {
    return this->name;
}

void Player::setIndexInsideTile(uint8_t index) {
    this->indexInsideTile = index;
}