/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

using namespace std;
using namespace sf;

int main() {
    Game *game = Game::getInstancePtr();
    ResourceManager *resourceManager = game->getResourceManagerPtr();
    SceneManager *sceneManager = game->getSceneManagerPtr();
    game->initWindow();

    /***************************/

    Sprite & board = sceneManager->addSprite("board", resourceManager->addTexture("board", "../textures/board.png"));
    sceneManager->addSound("coin flip", resourceManager->addAudio("coin flip", "../sounds/coin.wav"));

    /// scale board
    board.setScale((float)game->getScreenSize().x / board.getLocalBounds().width,
                   (float)game->getScreenSize().y / board.getLocalBounds().height);

    cout<<*game;
    cout<<*resourceManager;
    cout<<*sceneManager;
    /***************************/
    game->loop();
    Game::clearInstance();
    return 0;
}
