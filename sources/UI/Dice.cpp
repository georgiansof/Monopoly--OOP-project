//
// Created by je_gi on 2023-12-10.
//
#include "../../headers/UI/Dice.hpp"
#include "../../headers/DataStructures/CustomExceptions.hpp"
#include "../../headers/Managers/ResourceManager.hpp"

using namespace std;
using namespace sf;

Dice::Dice(const sf::Vector2f& position, const sf::Vector2f& size)
        : Button(position, size, *textures[0]) {
}

void Dice::setTextureVec(int index, const sf::Texture *texture) {
    if(index < 0 || index >= 6)
        throw IndexOutOfBounds(index, typeid(sf::Texture).name());
    Dice::textures[index] = const_cast<Texture*>(texture); /// textures array could be const,
                                                          /// but value is not known from the start
}

sf::Texture*& Dice::getTextureVec(int index) {
    if(index < 0 || index >= 6)
        throw IndexOutOfBounds(index, typeid(sf::Texture).name());
    return Dice::textures[index];
}