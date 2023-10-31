//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_TAXTILE_HPP
#define OOP_TAXTILE_HPP

#include "BoardTile.hpp"

class TaxTile : protected BoardTile {
public:
    enum Type {INCOME, LUXURY};
private:
    const uint32_t amount;
    const TaxTile::Type type;
protected:
    TaxTile(TaxTile::Type type, unsigned short boardPosition, unsigned int amount)
            : BoardTile(boardPosition, TAX), amount(amount), type(type) {}
    [[nodiscard]] uint32_t getPrice() const noexcept;
public:
    TaxTile() = delete;
    ~TaxTile() = default;
};

#endif //OOP_TAXTILE_HPP
