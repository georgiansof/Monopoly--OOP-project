//
// Created by je_gi on 2023-11-16.
//
#include "../../headers/Tiles/Neighborhood.hpp"

float propertyHouseOffsetX[4] = {0.005, 0.025, 0.045, 0.065};
float propertyHouseOffsetY = 0.12;

float normalTileSize = 0.08;
float bigTileSize = 0.13;
float borderSize = 0.01;

using namespace std;

Neighborhood::Neighborhood(std::string & name, sf::Color color, unsigned short boardPosition, unsigned int price, const uint32_t *rentPrice)
        : Property(name, Property::Type::NEIGHBORHOOD, boardPosition, price), color(color) {
    houseLevel = 0;
    for(int i = 0; i < 6; ++i)
        this->rentPrice[i] = rentPrice[i];

    if(boardPosition >= 1 && boardPosition <= 9)
        for(int x_ind = 0; x_ind < 4; ++x_ind)
            housePositions[x_ind] = sf::Vector2f(
                    1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 1) - propertyHouseOffsetX[x_ind],
                    1.0f - borderSize - propertyHouseOffsetY
            );
    if(boardPosition >= 11 && boardPosition <= 19)
        for(int y_ind = 0; y_ind < 4; ++y_ind)
            housePositions[y_ind] = sf::Vector2f(
                    borderSize + propertyHouseOffsetY,
                    1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 11) - propertyHouseOffsetX[y_ind]
            );
    if(boardPosition >= 21 && boardPosition <= 29)
        for(int x_ind = 0; x_ind < 4; ++x_ind)
            housePositions[x_ind] = sf::Vector2f(
                    borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 21) + propertyHouseOffsetX[x_ind],
                    borderSize + propertyHouseOffsetY
            );
    if(boardPosition >= 31 && boardPosition <= 39)
        for(int y_ind = 0; y_ind < 4; ++y_ind)
            housePositions[y_ind] = sf::Vector2f(
                    1.0f - borderSize - propertyHouseOffsetY,
                    borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 31) + propertyHouseOffsetX[y_ind]
            );
}
Neighborhood::Neighborhood(const char* name, sf::Color color, unsigned short boardPosition, unsigned int price, const uint32_t *rentPrice)
        : Property(name, Property::Type::NEIGHBORHOOD, boardPosition, price), color(color) {
    houseLevel = 0;

    for(int i = 0; i < 6; ++i)
        this->rentPrice[i] = rentPrice[i];

    if(boardPosition >= 1 && boardPosition <= 9)
        for(int x_ind = 0; x_ind < 4; ++x_ind)
            housePositions[x_ind] = sf::Vector2f(
                    1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 1) - propertyHouseOffsetX[x_ind],
                    1.0f - borderSize - propertyHouseOffsetY
            );
    if(boardPosition >= 11 && boardPosition <= 19)
        for(int y_ind = 0; y_ind < 4; ++y_ind)
            housePositions[y_ind] = sf::Vector2f(
                    borderSize + propertyHouseOffsetY,
                    1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 11) - propertyHouseOffsetX[y_ind]
            );
    if(boardPosition >= 21 && boardPosition <= 29)
        for(int x_ind = 0; x_ind < 4; ++x_ind)
            housePositions[x_ind] = sf::Vector2f(
                    borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 21) + propertyHouseOffsetX[x_ind],
                    borderSize + propertyHouseOffsetY
            );
    if(boardPosition >= 31 && boardPosition <= 39)
        for(int y_ind = 0; y_ind < 4; ++y_ind)
            housePositions[y_ind] = sf::Vector2f(
                    1.0f - borderSize - propertyHouseOffsetY,
                    borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 31) + propertyHouseOffsetX[y_ind]
            );
}

void Neighborhood::onVisit(Player *plyr) {
    if(this->owner != nullptr) {
        auto playerOwnsNeighbds = plyr->getTilesOwnedOfType<Neighborhood>();
        int sameColorCount = 0;
        for(auto ngb : playerOwnsNeighbds)
            if(this->color == ngb->color)
                ++sameColorCount;

        bool doubleRent = false;
        if(sameColorCount == 3
        || (sameColorCount == 2 && this->isSmallNeighborHood()))
            doubleRent = true;

        uint32_t fee = rentPrice[houseLevel];
        if(houseLevel == 0 && doubleRent)
            fee *= 2;

        bool successfulPayment = plyr->payTo(owner, fee);
        if(!successfulPayment) {
            plyr->waitToPay(owner, fee); /// TODO payment
            cout<<"Current player has to sell because of insufficient balance!\n";
        }
        return;
    }
    /// else if not owned
    Property::offerFromBank(plyr);
}

bool Neighborhood::isSmallNeighborHood() const {
    if(this->name == "Rahova"
    || this->name == "Giulesti"
    || this->name == "Primaverii"
    || this->name == "Magheru")
        return true;
    return false;
}

[[maybe_unused]] void Neighborhood::addHouse() {
    cout<<housePositions[1].x; /// warning dodge, to be implemented
}