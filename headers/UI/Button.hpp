//
// Created by je_gi on 2023-12-10.
//

#ifndef OOP_BUTTON_HPP
#define OOP_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "UIElement.hpp"
#include "../../constants.hpp"

class Button : public UIElement {
    sf::Text text;
    bool showText = true;
    void (*action)() = &Globals::nullFunction;

    void constructText(
            const sf::Color& fontColor, uint32_t fontStyle,
            const sf::Vector2f& positionTLC_proc, const sf::Vector2f& size_proc);
public:
    Button(const std::string &text,
           const sf::Vector2f& positionTLC_proc,
           const sf::Vector2f& size_proc,
           const sf::Color& bgColor = sf::Color::White,
           const sf::Color& outlineColor = sf::Color::Black,
           float outlineThickness = OUTLINE_THICKNESS_DEFAULT,
           const sf::Color& fontColor = sf::Color::Black,
           sf::Text::Style fontStyle = sf::Text::Style::Regular,
           uint32_t fontSize = FONTSIZE_DEFAULT,
           void (*action)() = &Globals::nullFunction,
           const sf::Font& = Globals::getDefaultFont());
    Button(const sf::Vector2f& positionTLC_proc,
           const sf::Vector2f& size_proc,
           const sf::Texture &texture,
           void (*action)() = &Globals::nullFunction);

    Button(const Button& other);
    void draw(sf::RenderWindow *window) override;
    void onClick(sf::Mouse::Button click) override;
    void setPosition(const sf::Vector2f& position) override;
    void setText(const std::string& textstr);
};


#endif //OOP_BUTTON_HPP
