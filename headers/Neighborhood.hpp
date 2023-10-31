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
public:
    Neighborhood(std::string & name, sf::Color color, unsigned short boardPosition, unsigned int price)
        : Property(name, Property::Type::NEIGHBORHOOD, boardPosition, price), color(color) {}
    Neighborhood(const char* name, sf::Color color, unsigned short boardPosition, unsigned int price)
            : Property(name, Property::Type::NEIGHBORHOOD, boardPosition, price), color(color) {}
    Neighborhood() = delete;
    ~Neighborhood() = default;
};

#endif //OOP_NEIGHBORHOOD_HPP
