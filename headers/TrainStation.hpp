//
// Created by je_gi on 2023-10-31.
//

#ifndef OOP_TRAINSTATION_HPP
#define OOP_TRAINSTATION_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Property.hpp"

class TrainStation : public Property {
private:
    uint8_t index;
public:
    TrainStation(std::string & name, uint8_t index, unsigned int price)
            : Property(name, Property::Type::TRAIN_STATION, 5 + (index - 1) * 10, price),
            index(index) {
        if(index < 1 || index > 4)
            throw std::runtime_error("Train station index out of bounds!");
    }
    TrainStation(const char* name, uint8_t index, unsigned int price)
            : Property(name, Property::Type::TRAIN_STATION, 5 + (index - 1) * 10, price),
            index(index) {
        if(index < 1 || index > 4)
            throw std::runtime_error("Train station index out of bounds!");
    }
    TrainStation() = delete;
    ~TrainStation() = default;
};

#endif //OOP_TRAINSTATION_HPP
