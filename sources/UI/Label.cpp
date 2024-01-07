#include "../../headers/UI/Label.hpp"
#include <iostream>
#include "../../headers/Game.hpp"

using namespace sf;
using namespace std;

Label::Label(
        const std::string& _text,
        sf::Vector2f position,
        sf::Color _outlineColor,
        float _outlineThickness,
        uint32_t fontSize,
        sf::Color fontColor,
        sf::Text::Style fontStyle,
        const sf::Font& _font,
        sf::Vector2f wrapper_size,
        sf::Color wrapperColor)
            : UIElement(wrapperColor,
                        position,
                        wrapper_size) {

    position.y -= Game::getInstancePtr()->coordinateToPercentage((float)fontSize + _outlineThickness, Game::axis::Y) * 1.5f;
    this->text.setPosition(Game::getInstancePtr()->percentageToCoordinates(position));
    this->text.setFont(_font);
    this->text.setString(_text);
    this->text.setCharacterSize(fontSize);
    this->text.setStyle(fontStyle);
    this->text.setFillColor(fontColor);

    this->text.setOutlineColor(_outlineColor);
    this->text.setOutlineThickness(_outlineThickness);
}

Label::Label(
        const std::string& _text,
        const TextEntry& associatedTextbox,
        sf::Color _outlineColor,
        float _outlineThickness,
        uint32_t fontSize,
        sf::Color fontColor,
        sf::Text::Style fontStyle,
        const sf::Font& _font,
        sf::Vector2f wrapper_size,
        sf::Color wrapperColor)
        : UIElement(wrapperColor,
                    {associatedTextbox.getPosition().x, associatedTextbox.getPosition().y - Game::getInstancePtr()->coordinateToPercentage((float)fontSize + _outlineThickness, Game::axis::Y) * 1.5f},
                    wrapper_size) {

    this->text.setPosition(Game::getInstancePtr()->percentageToCoordinates({associatedTextbox.getPosition().x, associatedTextbox.getPosition().y - Game::getInstancePtr()->coordinateToPercentage((float)fontSize + _outlineThickness, Game::axis::Y) * 1.5f}));
    this->text.setFont(_font);
    this->text.setString(_text);
    this->text.setCharacterSize(fontSize);
    this->text.setStyle(fontStyle);
    this->text.setFillColor(fontColor);

    this->text.setOutlineColor(_outlineColor);
    this->text.setOutlineThickness(_outlineThickness);
}


void Label::onClick(sf::Mouse::Button button) {if(button!=sf::Mouse::Button::Left) return;}
void Label::onKeyPress(sf::Keyboard::Key key) {
    if(key==sf::Keyboard::Key::Apostrophe)
        cout<<'`'; // warninig dodge
}

void Label::draw(sf::RenderWindow *window) {
    window->draw(text);
}

void Label::setText(const std::string& textstr) {this->text.setString(textstr);}
void Label::appendText(const std::string& addStr) {
    this->text.setString(this->text.getString() + addStr);
}
[[maybe_unused]] std::string Label::getText() const noexcept {
    return this->text.getString();
}