//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_PROPERTY_HPP
#define OOP_PROPERTY_HPP

#include <string>
#include "BoardTile.hpp"
#include <SFML/Graphics.hpp>

class Property : public BoardTile {
public:
    enum Type {NEIGHBORHOOD, TRAIN_STATION, FACTORY};
protected:
    const Property::Type type;
    const std::string name;
    const uint32_t price;
    Player *owner = nullptr;
    Property(std::string & name, Type type, unsigned short boardPosition, unsigned int price);
    Property(const char *name, Type type, unsigned short boardPosition, unsigned int price);
public:
    [[nodiscard]] uint32_t getPrice() const noexcept;
    Property() = delete;
    ~Property() override = default;
    void onVisit(Player *plyr) override = 0;
    void offerFromBank(Player *who);
    void setOwner(Player *plyr);
};

#endif //OOP_PROPERTY_HPP
