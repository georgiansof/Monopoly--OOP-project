#include <iostream>
#include <chrono>
#include <thread>

#ifdef __linux__
#include <X11/Xlib.h>
#endif
/**--------------------------------------------------**/

#include "headers/game.h"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

int main() {
    Game::getInstance().init();
    Game::getInstance().loop();
    Game::clearInstance();
    return 0;
}
