#include "../headers/Property.hpp"


[[nodiscard]] uint32_t Property::getPrice() const noexcept {
    return this->price;
}

Property::Property(std::string & name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), type(type), name(name), price(price)  {

}

Property::Property(const char *name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), type(type), name(name), price(price) {

}