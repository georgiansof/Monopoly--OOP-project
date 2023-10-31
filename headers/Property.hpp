//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_PROPERTY_HPP
#define OOP_PROPERTY_HPP

#include <string>
#include "BoardTile.hpp"

class Property : protected BoardTile {
public:
    enum Type {NEIGHBORHOOD, TRAIN_STATION, FACTORY};
private:
    const Property::Type type;
    const std::string name;
    const uint32_t price;
protected:
    Property(std::string & name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), price(price), type(type), name(name) {}
    Property(const char *name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), price(price), type(type), name(name) {}
public:
    [[nodiscard]] uint32_t getPrice() const noexcept;
    Property() = delete;
    ~Property() = default;
};

#endif //OOP_PROPERTY_HPP
