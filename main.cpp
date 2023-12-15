/**-- MonOOPoly by georgiansof@2023 --***/
#define SDL_MAIN_HANDLED
/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

sf::Font* Globals::defaultFont = nullptr;
bool Globals::capsLock = false;
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
    SceneManager *sceneManager = game->getSceneManagerPtr(); /// stored objects are drawn
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

    ///--------------------------------
    /*
    try {
        Sprite &board = sceneManager->addSprite("board", resourceManager->getTexture("board"));
        sceneManager->addSound("coin flip", resourceManager->getAudio("coin flip"));
        /// scale board to screen
        board.setScale((float) game->getWindowSize().x / board.getLocalBounds().width,
                       (float) game->getWindowSize().y / board.getLocalBounds().height);
    }
    catch(exception &e) {
        return handleFatalException(e);
    }

    /// ADD TILES

    try {game->addTiles();}
    catch (exception &e) {
        return handleFatalException(e);
    }
    ///  ADD PLAYERS
    try {
        game->addPlayer(new Player("Gigi", Color(0, 0, 0), PLAYER_START_MONEY));
        game->addPlayer(new Player("Giani", Color::Yellow));
        game->addPlayer(new Player("Geo", Color::Green));
        game->addPlayer(new Player("Gabi", Color::Red));
        game->addPlayer(new Player("Geralt", Color::Magenta));
        game->addPlayer(new Player("George", Color::Blue));
        game->addPlayer(new Player("Georgian", Color::Cyan));
        game->addPlayer(new Player("Georgiana", Color::White));

        game->addPlayer(new Player("Bog", Color::Transparent));
    }
    catch(std::exception &e) {
        if(dynamic_cast<FatalException*>(&e) == nullptr)
            std::cerr << e.what();
        else
            handleFatalException(e);
    }
    */
    game->loop();
    Game::clearInstance();

    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
