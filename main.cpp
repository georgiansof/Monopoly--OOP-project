/**-- MonOOPoly by georgiansof@2023 --***/
#define SDL_MAIN_HANDLED
/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

sf::Font* Globals::defaultFont = nullptr;
bool Globals::repeatKeyPressed = false;

Game* Game::instance = nullptr;

sf::Texture* Dice::textures[6];

using namespace std;
using namespace sf;


int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    Game *game = Game::getInstancePtr();
    ResourceManager *resourceManager = game->getResourceManagerPtr(); /// loads from files
    UIManager *uiManager = game->getuiManagerPtr();

    game->initWindow();

    resourceManager->addFont("arial","../fonts/arial.ttf");
    Globals::setDefaultFont(&resourceManager->getFont("arial"));

    resourceManager->addTexture("board", "../textures/board.png");
    resourceManager->addAudio("coin flip", "../sounds/coin.wav");
    for(int i = 1; i <= 6; ++i)
        resourceManager->addTexture(std::string("dice") + to_string(i),
                                             std::string("../textures/dice") + std::to_string(i) + string(".png"));
    uiManager->createDices(resourceManager);
    uiManager->hideDices();
    game->constructMainMenuUI();

    /// main menu flow -> manages connections -> finishes -> is destroyed -> board is drawn -> game starts

    game->loop();
    Game::clearInstance();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
