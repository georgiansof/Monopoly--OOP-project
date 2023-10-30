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
    ResourceManager* getResourceManagerPtr() noexcept;
    SceneManager* getSceneManagerPtr() noexcept;
    static Game * getInstancePtr();
    sf::Vector2<unsigned int> getScreenSize() const;
    static void clearInstance();
    void initWindow();
    void loop();
    void draw();
    friend std::ostream& operator<< (std::ostream& os, const Game& game); /// prints game details
};

#endif //OOP_GAME_H
