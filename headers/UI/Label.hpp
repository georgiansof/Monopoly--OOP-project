//
// Created by je_gi on 2023-12-10.
//

#ifndef OOP_LABEL_HPP
#define OOP_LABEL_HPP

#include "UIElement.hpp"
#include <SFML/Graphics.hpp>
#include "../../constants.hpp"

#define LABEL_DEFAULT_FONT_COLOR sf::Color::White

class TextEntry;

class Label : public UIElement {
public:sf::Text text;
public:
    Label() = delete;
    Label(const std::string& text,
          sf::Vector2f position,
          sf::Color outlineColor = sf::Color::Transparent,
          float outlineThickness = 0.0f,
          uint32_t fontSize = FONTSIZE_DEFAULT,
          sf::Color fontColor = LABEL_DEFAULT_FONT_COLOR,
          sf::Text::Style fontStyle = sf::Text::Style::Regular,
          const sf::Font& _font = Globals::getDefaultFont(),
          sf::Vector2f wrapper_size = {0,0},
          sf::Color wrapperColor = sf::Color::Transparent
          );
    Label(const std::string& text,
          const TextEntry& associatedTextbox,
          sf::Color outlineColor = sf::Color::Transparent,
          float outlineThickness = 0.0f,
          uint32_t fontSize = FONTSIZE_DEFAULT,
          sf::Color fontColor = LABEL_DEFAULT_FONT_COLOR,
          sf::Text::Style fontStyle = sf::Text::Style::Regular,
          const sf::Font& _font = Globals::getDefaultFont(),
          sf::Vector2f wrapper_size = {0,0},
          sf::Color wrapperColor = sf::Color::Transparent
    );
    Label(Label&) = default;
    void onClick(sf::Mouse::Button button) override;
    void onKeyPress(sf::Keyboard::Key key) override;
    void draw(sf::RenderWindow *window) override;
    void setText(const std::string& textstr);
};

#endif //OOP_LABEL_HPP
