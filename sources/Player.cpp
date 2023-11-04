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
