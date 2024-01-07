#include "../../headers/Managers/UIManager.hpp"
#include <iostream>
#include "../../headers/DataStructures/CustomExceptions.hpp"
#include "../../headers/Game.hpp"

using namespace std;

UIManager::~UIManager() {
    delete dice1;
    delete dice2;
    for(auto &elem : elements)
        delete elem.second;
    elements.clear();
}

void UIManager::addElement(const std::string& name, UIElement *elem) {
    this->elements.insert(make_pair(name,elem));
}

void UIManager::createDices(ResourceManager *resourceManager) {
    for(int i = 0; i < 6; ++i)
        Dice::setTextureVec(i,
                            &resourceManager->getTexture(std::string("dice") + std::to_string(i+1)));

    if(!dice1)
        dice1 = new Dice(DICE1_POSITION);
    else
        std::cerr << "Dice1 already exists! createDices() ignored.";

    if(!dice2)
        dice2 = new Dice(DICE2_POSITION);
    else
        std::cerr << "Dice2 already exists! createDices() ignored.";
}

void UIManager::hideDices() {dice1->hide(); dice2->hide();}
[[maybe_unused]] void UIManager::unhideDices() {dice1->unhide(); dice2->unhide();}

[[maybe_unused]] void UIManager::hideElement(const std::string& name) {
    auto find = elements.find(name);
    if(find == elements.end())
        throw SceneObjectNotFoundException(name);

    find->second->hide();
}

[[maybe_unused]] void UIManager::unhideElement(const std::string& name) {
    auto find = elements.find(name);
    if(find == elements.end())
        throw SceneObjectNotFoundException(name);

    find->second->unhide();
}

[[maybe_unused]] void UIManager::hideElement(UIElement *elem) {elem->hide();}
[[maybe_unused]] void UIManager::unhideElement(UIElement *elem) {elem->unhide();}

[[maybe_unused]] void UIManager::temporarilyShow(UIElement *elem, float seconds) {
    elem->showForSeconds(seconds);
}

void UIManager::removeElement(const std::string &name) {
    UIElement *elem = getElement(name);
    delete elem;
    elements.erase(name);
}


[[maybe_unused]] void UIManager::temporarilyShow(const std::string &name, float seconds) {
    auto find = elements.find(name);
    if(find == elements.end())
        throw SceneObjectNotFoundException(name);

    find->second->showForSeconds(seconds);
}

UIElement * UIManager::getElement(const std::string &name) {
    auto result = elements.find(name);
    if(result == elements.end())
        return nullptr;
    else
        return result->second;
}

void UIManager::updateMoneyLabel() {
    Game *game = Game::getInstancePtr();
    Label *lbl = dynamic_cast<Label*> (
            getElement("host_money"));
    lbl->setText("Your money: " + to_string(game->getPlayerByName(game->getHostName())->getAvailableMoney()) + "M");
}