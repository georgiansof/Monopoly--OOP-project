/// global includes

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

int main() {
    Game::getInstance().initWindow();
    /***************************/
    
    /***************************/
    Game::getInstance().loop();
    Game::clearInstance();
    return 0;
}
