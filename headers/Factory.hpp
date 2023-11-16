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
public:
    Factory(Factory::Type type, unsigned short boardPosition, unsigned int price, uint32_t feeMultiplierWithOne, uint32_t feeMultiplierWithTwo)
            : Property(type == WATER ? "Water Factory" : "Electricity Factory",
                       Property::Type::NEIGHBORHOOD, boardPosition, price),
             type(type), feeMultiplierWithOne(feeMultiplierWithOne),
             feeMultiplierWithTwo(feeMultiplierWithTwo) {}
    Factory() = delete;
    ~Factory() = default;
};

#endif //OOP_FACTORY_HPP
