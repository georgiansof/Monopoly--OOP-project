//
// Created by je_gi on 2023-12-10.
//
#include "../../headers/UI/Dice.hpp"
#include "../../headers/DataStructures/CustomExceptions.hpp"
#include "../../headers/Managers/ResourceManager.hpp"
#include "../../headers/Player.hpp"
#include "../../headers/Game.hpp"

using namespace std;
using namespace sf;

Dice::Dice(const sf::Vector2f& position, const sf::Vector2f& size)
        : Button(position, size, *textures[0]) {
}

void Dice::setTextureVec(int index, const sf::Texture *texture) {
    if(index < 0 || index >= 6)
        throw IndexOutOfBounds(index, typeid(sf::Texture).name());
    Dice::textures[index] = const_cast<Texture*>(texture); /// textures array could be const,
                                                          /// but value is not known from the start
}

sf::Texture*& Dice::getTextureVec(int index) {
    if(index < 0 || index >= 6)
        throw IndexOutOfBounds(index, typeid(sf::Texture).name());
    return Dice::textures[index];
}

void Dice::onClick(sf::Mouse::Button click) {
    Game *game = Game::getInstancePtr();
    Player *currentPlayer =
            *game->getCurrentPlayerIterator();

    if(currentPlayer->getName() == game->getHostName()) {
        pair<uint8_t, uint8_t> dices;
        dices = game->diceRoll();
        std::string broadcastMsg = string("rolled ") + game->getHostName() + " " + to_string(dices.first) + " " + to_string(dices.second);
        game->broadcast(broadcastMsg);
        game->eventClientReceivedInput(broadcastMsg); /// also for server
    }
    else
        cerr << "It's not your turn! It's " + currentPlayer->getName() <<"'s turn and you are " << game->getHostName() <<'\n';

}