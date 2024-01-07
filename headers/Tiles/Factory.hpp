#ifndef OOP_FACTORY_HPP
#define OOP_FACTORY_HPP

#include "Property.hpp"

class Factory : public Property {
public:
    enum Type {ELECTRICITY, WATER};
private:
    Type type;
    uint32_t feeMultiplierWithOne;
    uint32_t feeMultiplierWithTwo;

    static volatile uint8_t dice1,dice2;
public:
    static void setDices(uint8_t dice1, uint8_t dice2);
    void onVisit(Player *plyr) override;
    Factory(Factory::Type type, unsigned short boardPosition, unsigned int price, uint32_t feeMultiplierWithOne, uint32_t feeMultiplierWithTwo)
            : Property(type == WATER ? "Water Factory" : "Electricity Factory",
                       Property::Type::FACTORY, boardPosition, price),
             type(type), feeMultiplierWithOne(feeMultiplierWithOne),
             feeMultiplierWithTwo(feeMultiplierWithTwo) {}
    Factory() = delete;
    ~Factory() override = default;
};

#endif //OOP_FACTORY_HPP
