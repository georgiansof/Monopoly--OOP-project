//
// Created by je_gi on 2023-12-09.
//
#include "../../headers/Game.hpp"
#include "../../headers/UI/UIElement.hpp"
#include "../../constants.hpp"

using namespace sf;
using namespace std;

UIElement::UIElement(const sf::Color &color,
                     const sf::Vector2f& positionTLC_proc,
                     const sf::Vector2f& size_proc,
                     bool invisible,
                     float outlineThickness,
                     sf::Color outlineColor) {
    this->size = size_proc;
    this->position = positionTLC_proc;
    this->shapeType = shapeType::RECTANGULAR;
    this->invisible = invisible;
    Vector2<unsigned> screenSize = Game::getInstancePtr()->getWindowSize();
    Vector2<float> _position = {positionTLC_proc.x * (float)screenSize.x, positionTLC_proc.y * (float)screenSize.y};
    Vector2<float> _size = {size_proc.x * (float)screenSize.x, size_proc.y * (float)screenSize.y};
    this->shape = new RectangleShape(_size);

    this->shape->setPosition(_position);
    this->shape->setFillColor(color);
    this->shape->setOutlineThickness(outlineThickness);
    this->shape->setOutlineColor(outlineColor);
}

UIElement::UIElement(const sf::Texture &texture,
                     const sf::Vector2f& positionTLC_proc, const sf::Vector2f& size_proc,
                     bool invisible) {
    this->size = size_proc;
    this->position = positionTLC_proc;
    this->textured = true;
    this->shapeType = shapeType::RECTANGULAR;
    this->invisible = invisible;
    Vector2<unsigned> screenSize = Game::getInstancePtr()->getWindowSize();
    Vector2<float> _position = {positionTLC_proc.x * (float)screenSize.x, positionTLC_proc.y * (float)screenSize.y};
    Vector2<float> _size = {size_proc.x * (float)screenSize.x, size_proc.y * (float)screenSize.y};
    this->shape = new RectangleShape(_size);

    this->shape->setPosition(_position);
    //this->shape->setTextureRect(sf::IntRect(sf::Vector2i(position),sf::Vector2i(size)));
    this->shape->setTexture(&texture);
    this->shape->setOutlineThickness(0);
    this->shape->setOutlineColor(sf::Color::Transparent);
}

UIElement::UIElement(const UIElement& other) {
    switch(other.shapeType) {
        case shapeType::RECTANGULAR: {
            this->textured = other.textured;
            this->shapeType = other.shapeType;
            this->invisible = other.invisible;
            this->size = other.size;
            this->position = other.position;
            Vector2f sizePx = Game::getInstancePtr()->percentageToCoordinates(other.size);
            this->shape = new RectangleShape(sizePx);
            this->shape->setPosition(Game::getInstancePtr()->percentageToCoordinates(this->position));
            this->shape->setTexture(other.shape->getTexture());
            this->shape->setOutlineThickness(other.shape->getOutlineThickness());
            this->shape->setOutlineColor(other.shape->getOutlineColor());
            break;
        }
        default:
            std::cerr << "UIELEM OF FORM OTHER THAN RECTANGULAR NOT IMPLEMENTED\n";
            break;
    }
}

UIElement::~UIElement() {
    delete shape;
}

void UIElement::draw(sf::RenderWindow *window) {
    window->draw(*shape);
}

bool UIElement::isInvisible() const noexcept {
    return this->invisible;
}

bool UIElement::contains(sf::Vector2f position) const { /// TOFIX window resizing
    Vector2f fposition = {(float)position.x, (float)position.y};
    Vector2f shapePosition =
            this->position;
    Vector2f shapeSize =
            this->size;


    if(fposition.x < shapePosition.x
    || fposition.x > shapePosition.x + shapeSize.x
    || fposition.y < shapePosition.y
    || fposition.y > shapePosition.y + shapeSize.y)
        return false;
    return true;
}

const sf::Shape& UIElement::getShape() const {
    return *this->shape;
}

void UIElement::onClick(sf::Mouse::Button button) {}
void UIElement::onKeyPress(sf::Keyboard::Key key) {}
void UIElement::onClickOutside(sf::Mouse::Button button) {}
void UIElement::onTextEntered(char chr) {}

void UIElement::hide() {this->invisible = true; this->timerOn = false;}
void UIElement::unhide() {
    this->invisible = false;
}

bool UIElement::isEnter(char chr) noexcept {
    return chr == '\r' || chr == '\n';
}

void UIElement::showForSeconds(float seconds) {
    timerStamp = std::chrono::steady_clock::now();
    visibleTime = seconds;
    timerOn = true;
    this->unhide();
}

bool UIElement::isTimerOn() const {return this->timerOn;}
float UIElement::getVisibleTime() const {return this->visibleTime;}
std::chrono::time_point<std::chrono::steady_clock> UIElement::getTimerStart() const {
    return this->timerStamp;
}

void UIElement::setPosition(const sf::Vector2f &position) {
    auto coordPosition = Game::getInstancePtr()->percentageToCoordinates(position);
    this->shape->setPosition(coordPosition);
    this->position = position;
}

sf::Vector2f UIElement::getPosition() const noexcept {
    return this->position;
}

void UIElement::setSize(const sf::Vector2f &size) {
    auto coordSize = Game::getInstancePtr()->percentageToCoordinates(size);
    this->shape->setPosition(coordSize);
}

sf::Vector2f UIElement::getSize() const noexcept {
    auto coordposition = this->shape->getGlobalBounds().getSize();
    return Game::getInstancePtr()->coordinatesToPercentage(coordposition);
}

/*sf::Vector2f UIElement::getNearPosition(side_t side, const UIElement& other) const {
    Vector2f TLCposition = shape->getGlobalBounds().getPosition();
    Vector2f size = shape->getGlobalBounds().getSize();
    Vector2f BRCposition = TLCposition + size;

    switch(side) {
        case LEFT:

            break;
        case RIGHT:
            break;
        case UP:
            break;
        case DOWN:
            break;
    }
}*/