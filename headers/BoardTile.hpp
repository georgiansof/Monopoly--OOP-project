//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_BOARDTILE_HPP
#define OOP_BOARDTILE_HPP

#include <cstdint>

class BoardTile {
public:
    enum Type {JAIL, PROPERTY, TAX, PARK, CHANCE};
private:
    const uint16_t boardPosition;
    const BoardTile::Type type;
protected:
    explicit BoardTile(uint16_t boardPosition, BoardTile::Type type = PROPERTY)
        : boardPosition(boardPosition), type(type) {}
    [[nodiscard]] uint16_t getBoardPosition() const noexcept;
public:
    BoardTile() = delete;
    ~BoardTile() = default;
};



#endif //OOP_BOARDTILE_HPP
