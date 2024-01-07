//
// Created by je_gi on 2023-12-10.
//

#ifndef OOP_TEXTENTRY_HPP
#define OOP_TEXTENTRY_HPP

#include "Label.hpp"
#include "../../constants.hpp"
//#include "../Game.hpp"

class TextEntry : public UIElement {
public:
    enum chrType {ANY=1, LETTERS=1<<1, NUMBERS=1<<2, DOT=1<<3, COLON=1<<4, SPACE=1<<5};
    typedef uint8_t charType;
private:
    sf::Text textInside;
    std::string text;
    bool focused = false;
    int maxChr = INT_MAX;
    charType charTypeMask = ANY;
public:
    TextEntry() = delete;
    [[maybe_unused]] TextEntry(sf::Vector2f position,
              sf::Vector2f size,
              sf::Color insideColor = sf::Color::White,
              float outlineThickness = OUTLINE_THICKNESS_DEFAULT,
              sf::Color outlineColor = sf::Color::Blue,
              uint32_t fontSize = FONTSIZE_DEFAULT,
              sf::Color fontColor = sf::Color::Black,
              sf::Text::Style fontStyle = sf::Text::Style::Regular,
              const sf::Font& _font = Globals::getDefaultFont(),
              std::string insideText = "");
    TextEntry(sf::Vector2f position,
              float sizeX,
              int _maxChr,
              charType _charTypeMask = ANY,
              sf::Color insideColor = sf::Color::White,
              float outlineThickness = OUTLINE_THICKNESS_DEFAULT,
              sf::Color outlineColor = sf::Color::Blue,
              uint32_t fontSize = FONTSIZE_DEFAULT,
              sf::Color fontColor = sf::Color::Black,
              sf::Text::Style fontStyle = sf::Text::Style::Regular,
              const sf::Font& _font = Globals::getDefaultFont(),
              std::string insideText = "");
    void draw(sf::RenderWindow *window) override;
    void onClick(sf::Mouse::Button button) override;
    void onClickOutside(sf::Mouse::Button button) override;
    void onTextEntered(char chr) override;

    [[maybe_unused]] uint32_t getFontSize() const;
    void setCharType(uint8_t _charTypeMask);
    void setMaxLength(int len);
    void setText(std::string str);
    const std::string& getText() const;

    static bool isCharAllowed(char c, charType ctm);
};

#endif //OOP_TEXTENTRY_HPP
