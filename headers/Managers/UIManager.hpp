//
// Created by je_gi on 2023-12-09.
//

#ifndef OOP_UIMANAGER_HPP
#define OOP_UIMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "../UI/UIElement.hpp"
#include "../UI/Button.hpp"
#include "../UI/Dice.hpp"
#include "../UI/Label.hpp"
#include "../UI/TextEntry.hpp"
#include "../../constants.hpp"
#include "ResourceManager.hpp"

class Game;

class UIManager {
    sf::RectangleShape background;
    std::map<std::string, UIElement*> elements;
    Dice *dice1;
    Dice *dice2;
    friend Game;
public:
    UIManager() : dice1(nullptr), dice2(nullptr) {}
    ~UIManager();
    void addElement(const std::string& name, UIElement* elem);
    void removeElement(const std::string& name);
    void createDices(ResourceManager *resourceManager);
    void hideDices();
    [[maybe_unused]] void unhideDices();
    [[maybe_unused]] static void hideElement(UIElement *elem);
    [[maybe_unused]] void hideElement(const std::string& name);
    [[maybe_unused]] static void unhideElement(UIElement *elem);
    [[maybe_unused]] void unhideElement(const std::string& name);
    [[maybe_unused]] void temporarilyShow(const std::string& name, float seconds);
    [[maybe_unused]] static void temporarilyShow(UIElement *elem, float seconds);
    UIElement* getElement(const std::string & name);
    void updateMoneyLabel();
};

#endif //OOP_UIMANAGER_HPP
