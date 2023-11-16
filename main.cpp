/**-- MonOOPoly by georgiansof@2023 --***/

/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

using namespace std;
using namespace sf;

int handleFatalException(exception &e) {
    std::cerr << e.what();
    auto fatalExceptCast = dynamic_cast<fatalException*>(&e);
    if(fatalExceptCast == nullptr)
        return UNHANDLED_ERROR_CODE;
    else
        return fatalExceptCast->getExitCode();
}

int main() {
    Game *game = Game::getInstancePtr();
    ResourceManager *resourceManager = game->getResourceManagerPtr(); /// loads from files
    SceneManager *sceneManager = game->getSceneManagerPtr(); /// stored objects are drawn
    game->initWindow();

    /***************************/
    try {
        resourceManager->addTexture("blank", "../textures/blank.png");

        Sprite &board = sceneManager->addSprite("board", resourceManager->addTexture("board", "../textures/board.png"));
        sceneManager->addSound("coin flip", resourceManager->addAudio("coin flip", "../sounds/coin.wav"));

        /// scale board to screen
        board.setScale((float) game->getScreenSize().x / board.getLocalBounds().width,
                       (float) game->getScreenSize().y / board.getLocalBounds().height);
    }
    catch(exception &e) {
        return handleFatalException(e);
    }

    /// ADD TILES

    try {game->addTiles();}
    catch (exception &e) {
        return handleFatalException(e);
    }

    /***************  ADD PLAYERS *******************/
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
        if(dynamic_cast<fatalException*>(&e) == nullptr)
            std::cerr << e.what();
        else
            handleFatalException(e);
    }
    /***************************/

    cout<<*game;
    cout<<*resourceManager;
    cout<<*sceneManager;

    game->loop();
    Game::clearInstance();
    return 0;
}
