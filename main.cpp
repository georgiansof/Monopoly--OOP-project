/**-- MonOOPoly by georgiansof@2023 --***/

/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

std::vector<ChanceCard*> ChanceTile::adminBudgetCards;
std::vector<ChanceCard*> ChanceTile::supriseCards;

using namespace std;
using namespace sf;

int main() {
    Game *game = Game::getInstancePtr();
    ResourceManager *resourceManager = game->getResourceManagerPtr(); /// loads from files
    SceneManager *sceneManager = game->getSceneManagerPtr(); /// stored objects are drawn
    game->initWindow();

    /***************************/

    Sprite & board = sceneManager->addSprite("board", resourceManager->addTexture("board", "../textures/board.png"));
    sceneManager->addSound("coin flip", resourceManager->addAudio("coin flip", "../sounds/coin.wav"));

    /// scale board to screen
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
