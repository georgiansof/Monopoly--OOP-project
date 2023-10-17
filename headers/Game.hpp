#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef __linux__
#include <X11/Xlib.h>
#endif
#include <chrono>
#include <thread>

#include "ResourceManager.hpp"

class Game {
private:
    Game();
    ~Game() = default;
    static Game* instance;

    sf::RenderWindow window;
    //ResourceManager resourceManager;

public:
    static Game & getInstance();
    static void clearInstance();
    void initWindow();
    void loop();
};

#endif //OOP_GAME_H
