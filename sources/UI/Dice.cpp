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

    pair<uint8_t, uint8_t> dices;
    dices = game->diceRoll();
    game->broadcast(to_string(dices.first));

    if(currentPlayer->getName() == game->getHostName()) {
        /*if(game->getHostType() == Game::SERVER) {
            dices = Game::diceRoll();
        }
        else {
            game->getConnectionToServer()->Send("request diceroll");
            dices.first = stoi(game->getConnectionToServer()->Receive());
            dices.second = stoi(game->getConnectionToServer()->Receive());
        }*///partially incorrect
    }



    /*if(game->getHostType() == Game::CLIENT) {
        dices.first = stoi(game->getConnectionToServer()->Receive(NO_TIMEOUT));
        dices.second = stoi(game->getConnectionToServer()->Receive(NO_TIMEOUT));
    }
    else { /// SERVER
        dices = Game::diceRoll();
        for(auto connection : game->getConnectionsToClients()) {
            connection->Send(to_string(dices.first));
            connection->Send(to_string(dices.second));
        }
    }*/

    //std::cout << dices.first << ' ' << dices.second << '\n';
}