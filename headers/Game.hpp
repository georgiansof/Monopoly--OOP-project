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
#include "SceneManager.hpp"

class Game {
private:
    Game();
    ~Game() = default;
    static Game* instance;

    std::string details;
    sf::RenderWindow window;
    ResourceManager resourceManager;
    SceneManager sceneManager;
public:
    ResourceManager* getResourceManagerPtr();
    SceneManager* getSceneManagerPtr();
    static Game * getInstancePtr();
    static void clearInstance();
    void initWindow();
    void loop();
    void draw(const sf::Sprite & sprite);
    friend std::ostream& operator<< (std::ostream& os, const Game& game); /// prints game details
};

#endif //OOP_GAME_H
