//
// Created by je_gi on 2023-12-09.
//

#ifndef OOP_UIELEMENT_HPP
#define OOP_UIELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <chrono>

class UIManager;

class UIElement {
public:
    enum shapeType {RECTANGULAR}; //CIRCULAR};
    enum side_t {UP};//,LEFT,RIGHT,DOWN};
protected:
    sf::Shape *shape = nullptr;
    sf::Vector2f position;
    sf::Vector2f size;
    bool invisible;
    shapeType shapeType;
    std::chrono::time_point<std::chrono::steady_clock> timerStamp;
    float visibleTime = 0;
    bool timerOn = false;
    bool textured = false;
public:
    UIElement() = delete;
    UIElement(const sf::Color& color,
              const sf::Vector2f& positionTLC_proc,
              const sf::Vector2f& size_proc,
              bool invisible = false,
              float outlineThickness = 0.0f,
              sf::Color outlineColor = sf::Color::Black);
    UIElement(const sf::Texture& texture,
              const sf::Vector2f& positionTLC_proc,
              const sf::Vector2f& size_proc,
              bool invisible = false);
    UIElement(const UIElement& other);
    virtual ~UIElement();

    [[nodiscard]] bool isInvisible() const noexcept;
    void hide();
    void unhide();
    void showForSeconds(float seconds);
    [[nodiscard]] bool isTimerOn() const;
    [[nodiscard]] float getVisibleTime() const;
    [[nodiscard]] std::chrono::time_point<std::chrono::steady_clock> getTimerStart() const;

    virtual void onClick(sf::Mouse::Button button);
    virtual void onClickOutside(sf::Mouse::Button button);
    virtual void onKeyPress(sf::Keyboard::Key key);
    virtual void onTextEntered(char chr);
    virtual void draw(sf::RenderWindow *window) = 0;
    [[nodiscard]] const sf::Shape& getShape() const;
    [[nodiscard]] bool contains(sf::Vector2f position) const;
    static bool isEnter(char chr) noexcept;

    virtual void setPosition(const sf::Vector2f& position);
    virtual void setSize(const sf::Vector2f& size);
    [[nodiscard]] sf::Vector2f getPosition() const noexcept;
    [[nodiscard]] sf::Vector2f getSize() const noexcept;
};



#endif //OOP_UIELEMENT_HPP
