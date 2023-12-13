#include "../../headers/UI/TextEntry.hpp"

using namespace std;
using namespace sf;

#include "../../headers/Game.hpp"

TextEntry::TextEntry(sf::Vector2f position,
                     sf::Vector2f size,
                     sf::Color insideColor,
                     float outlineThickness,
                     sf::Color outlineColor,
                     uint32_t fontSize,
                     sf::Color fontColor,
                     sf::Text::Style fontStyle,
                     const sf::Font& _font,
                     std::string insideText)
    : UIElement(insideColor, position,
            size, false,
             outlineThickness, outlineColor), text(std::move(insideText)) {

    Vector2f windowPosition = position;
    windowPosition.x *= (float)Game::getInstancePtr()->getWindowSize().x;
    windowPosition.y *= (float)Game::getInstancePtr()->getWindowSize().y;

    this->textInside.setPosition({windowPosition.x + 0.01f * size.x, windowPosition.y + 0.01f * size.y});
    this->textInside.setFont(_font); /// not working default
    this->textInside.setString(this->text);
    this->textInside.setCharacterSize(fontSize);
    this->textInside.setStyle(fontStyle);
    this->textInside.setFillColor(fontColor);

}

TextEntry::TextEntry(sf::Vector2f position,
                     float sizeX,
                     int _maxChr,
                     charType _charTypeMask,
                     sf::Color insideColor,
                     float outlineThickness,
                     sf::Color outlineColor,
                     uint32_t fontSize,
                     sf::Color fontColor,
                     sf::Text::Style fontStyle,
                     const sf::Font& _font,
                     std::string insideText)
        : UIElement(insideColor, position,
                    sf::Vector2f(sizeX, (float)fontSize / (float)Game::getInstancePtr()->getWindowSize().y * 1.2f), false,
                    outlineThickness, outlineColor), text(std::move(insideText)) {

    this->maxChr = _maxChr;
    this->charTypeMask = _charTypeMask;
    Vector2f windowPosition = position;
    windowPosition.x *= (float)Game::getInstancePtr()->getWindowSize().x;
    windowPosition.y *= (float)Game::getInstancePtr()->getWindowSize().y;

    this->textInside.setPosition({windowPosition.x + 0.01f * (float)fontSize / sizeX * 1.2f, windowPosition.y + 0.01f * (float)fontSize / (float)Game::getInstancePtr()->getWindowSize().y * 1.2f});
    this->textInside.setFont(_font); /// not working default
    this->textInside.setString(this->text);
    this->textInside.setCharacterSize(fontSize);
    this->textInside.setStyle(fontStyle);
    this->textInside.setFillColor(fontColor);

}

void TextEntry::draw(sf::RenderWindow *window) {
    UIElement::draw(window);
    window->draw(textInside);
}

void TextEntry::onClick(sf::Mouse::Button button) {
    switch(button) {
        case sf::Mouse::Button::Left:
            this->focused = true;
            break;
        default:
            break;
    }
}

void TextEntry::onClickOutside(sf::Mouse::Button button) {
    switch(button) {
        case sf::Mouse::Button::Left:
            this->focused = false;
            break;
        default:
            break;
    }
}

bool TextEntry::isCharAllowed(char c, charType ctm) {
    if(ctm & ANY)
        return true;
    if(isdigit(c))
        return ctm & chrType::NUMBERS;
    if(toupper(c) != tolower(c))
        return ctm & chrType::LETTERS;
    if(c == ' ')
        return ctm & chrType::SPACE;
    if(c == '.')
        return ctm & chrType::DOT;
    if(c == ':')
        return ctm & chrType::COLON;
    return false;
}

void TextEntry::onTextEntered(char chr) {
    if(focused) {
        if (chr == BACKSPACE_ASCII) {
            if (!text.empty())
                text.pop_back();
        }
        else {
            if((int)text.size() < maxChr && !isEnter(chr) && isCharAllowed(chr, charTypeMask))
                text.push_back(chr);
            else {
                if(!isEnter(chr))
                    cerr << "Character " << chr << " not allowed in textBox.\n";
                else {
                    cerr << "Enter pressed in textBox.\n";
                }
            }
        }
    }

    textInside.setString(text);
}

uint32_t TextEntry::getFontSize() const {
    return this->textInside.getCharacterSize();
}

void TextEntry::setCharType(uint8_t _charTypeMask) {
    this->charTypeMask = _charTypeMask;
}

void TextEntry::setMaxLength(int len) {this->maxChr = len;}