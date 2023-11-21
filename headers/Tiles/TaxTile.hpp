//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_TAXTILE_HPP
#define OOP_TAXTILE_HPP

#include "BoardTile.hpp"

class TaxTile : public BoardTile {
public:
    enum Type {INCOME, LUXURY};
private:
    const uint32_t amount;
    const TaxTile::Type type;
public:
    TaxTile(TaxTile::Type type, unsigned short boardPosition, unsigned int amount)
            : BoardTile(boardPosition, TAX), amount(amount), type(type) {}
    //[[nodiscard]] uint32_t getAmount() const noexcept;
    TaxTile() = delete;
    ~TaxTile() = default;
};

#endif //OOP_TAXTILE_HPP
