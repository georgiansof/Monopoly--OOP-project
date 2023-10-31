#ifndef OOP_FACTORY_HPP
#define OOP_FACTORY_HPP

#include "Property.hpp"

class Factory : public Property {
public:
    enum Type {ELECTRICITY, WATER};
private:
    Type type;
public:
    Factory(Factory::Type type, unsigned short boardPosition, unsigned int price)
            : Property(type == WATER ? "Water Factory" : "Electricity Factory",
                       Property::Type::NEIGHBORHOOD, boardPosition, price) {}
    Factory() = delete;
    ~Factory() = default;
};

#endif //OOP_FACTORY_HPP
