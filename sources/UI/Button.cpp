#include "../../headers/UI/Button.hpp"
#include "../../headers/Game.hpp"

using namespace sf;

void Button::constructText(
        const sf::Color& fontColor,
        uint32_t fontStyle,
        const sf::Vector2f &positionTLC_proc,
        const sf::Vector2f &size_proc) {

    this->text.setFillColor(fontColor);
    this->text.setStyle(fontStyle);
    Vector2u screenSize = Game::getInstancePtr()->getWindowSize();
    Vector2f textPosition;
    textPosition.x = positionTLC_proc.x * (float)screenSize.x + size_proc.x * (float)screenSize.x / 2.0f - text.getGlobalBounds().getSize().x / 2.0f;
    textPosition.y = positionTLC_proc.y * (float)screenSize.y + size_proc.y * (float)screenSize.y / 2.0f - text.getGlobalBounds().getSize().y;
    text.setPosition(textPosition);
}

Button::Button(const std::string& textstr,
               const sf::Vector2f& positionTLC_proc,
               const sf::Vector2f& size_proc,
               const sf::Color& bgColor,
               const sf::Color& outlineColor,
               float outlineThickness,
               const sf::Color& fontColor,
               sf::Text::Style fontStyle,
               uint32_t fontSize,
               void (*_action)(),
               const sf::Font& font)
        : UIElement(bgColor, positionTLC_proc, size_proc, false, outlineThickness, outlineColor),
          text(textstr,font,fontSize) {
    this->showText = true;
    this->action = _action;
    constructText(fontColor, fontStyle, positionTLC_proc, size_proc);
}

Button::Button(const sf::Vector2f& positionTLC_proc, const sf::Vector2f& size_proc,
               const sf::Texture& texture,
               void (*_action)())
        : UIElement(texture, positionTLC_proc, size_proc) {
    this->showText = false;
    this->action = _action;
}

Button::Button(const Button& other)
        : UIElement(other), text(other.text.getString(),
                                 *other.text.getFont(),
                                 other.text.getCharacterSize()) {
    this->showText = other.showText;
    this->action = other.action;
    if(showText)
        this->constructText(other.text.getFillColor(),
                      other.text.getStyle(),
                      Game::getInstancePtr()->coordinatesToPercentage(other.shape->getGlobalBounds().getPosition()),
                      Game::getInstancePtr()->coordinatesToPercentage(other.shape->getGlobalBounds().getSize()));
}

void Button::draw(sf::RenderWindow *window) {
    UIElement::draw(window);
    if(this->showText)
        window->draw(text);
}

void Button::onClick(sf::Mouse::Button click) {
    if(!this->invisible)
        (*this->action)();
}

void Button::setText(const std::string& textstr) {
    this->text.setString(textstr);
}

void Button::setPosition(const sf::Vector2f &position) {
    UIElement::setPosition(position);

    Vector2f textSize = text.getGlobalBounds().getSize();
    Vector2f textSize_proc = Game::getInstancePtr()->coordinatesToPercentage(textSize);
    Vector2u screenSize = Game::getInstancePtr()->getWindowSize();
    Vector2f textPosition;
    textPosition.x = position.x * (float)screenSize.x + textSize_proc.x * (float)screenSize.x / 2.0f - text.getGlobalBounds().getSize().x / 2.0f;
    textPosition.y = position.y * (float)screenSize.y + textSize_proc.y * (float)screenSize.y / 2.0f - text.getGlobalBounds().getSize().y;
    text.setPosition(textPosition);
}