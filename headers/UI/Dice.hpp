//
// Created by je_gi on 2023-12-10.
//

#ifndef OOP_DICE_HPP
#define OOP_DICE_HPP

#include "Button.hpp"
#include "../../constants.hpp"

class Dice : public Button {
    static sf::Texture* textures[6];
public:
    static void setTextureVec(int index, const sf::Texture *texture);
    static sf::Texture*& getTextureVec(int index);
    explicit Dice(const sf::Vector2f& position, const sf::Vector2f& size = DICE_SIZE);
};

#endif //OOP_DICE_HPP