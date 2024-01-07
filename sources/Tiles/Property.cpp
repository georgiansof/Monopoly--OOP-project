#include "../../headers/Tiles/Property.hpp"
#include "../../headers/Game.hpp"

[[nodiscard]] uint32_t Property::getPrice() const noexcept {
    return this->price;
}

Property::Property(std::string & name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), type(type), name(name), price(price)  {

}

Property::Property(const char *name, Type type, unsigned short boardPosition, unsigned int price)
        : BoardTile(boardPosition, PROPERTY), type(type), name(name), price(price) {

}

void Property::offerFromBank(Player *plyr) {
    /// not owned
    bool buy = false;
    if(plyr->getAvailableMoney() > this->getPrice())
        buy = plyr->promptVisitorBuy(this);

    if(!buy) {
        //Game::getInstancePtr()->propertyLicitation(this);
        return;
    }
    /// else player bought station

    plyr->payToBank(this->getPrice());
    this->owner = plyr;
    plyr->addOwnedProperty(this);
}

void Property::setOwner(Player *plyr) {
    this->owner = plyr;
}