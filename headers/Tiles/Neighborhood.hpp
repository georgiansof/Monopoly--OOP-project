//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_NEIGHBORHOOD_HPP
#define OOP_NEIGHBORHOOD_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Property.hpp"

class Neighborhood : public Property {
private:
    const sf::Color color;
    sf::Vector2f housePositions[4];
    uint8_t houseLevel; /// 5 = hotel
    [[maybe_unused]] uint32_t rentPrice[6] {};
public:
    void onVisit(Player* plyr) override;
    Neighborhood(std::string & name, sf::Color color, unsigned short boardPosition, unsigned int price, const uint32_t *rentPrice);
    //Neighborhood(const char* name, sf::Color color, unsigned short boardPosition, unsigned int price, const uint32_t *rentPrice);
    Neighborhood() = delete;
    ~Neighborhood() override = default;
    [[nodiscard]] bool isSmallNeighborHood() const;
    [[maybe_unused]] void addHouse();
};

#endif //OOP_NEIGHBORHOOD_HPP
