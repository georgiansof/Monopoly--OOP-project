#include "../headers/Game.hpp"
#include <iostream>

Game::Game() {
    Game::instance = nullptr;
    this->details = "MonOOPoly game by georgiansof";
}

Game* Game::getInstancePtr() {
    if(Game::instance != nullptr)
        return Game::instance;
    else {
        Game::instance = new Game;
        return Game::instance;
    }
}

void Game::clearInstance() {
    delete Game::instance;
}

void Game::initWindow() {
#ifdef __linux__
    XInitThreads();
#endif
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    ///window.setFramerateLimit(60);
}
void Game::loop() {
    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << "New width: " << window.getSize().x << '\n'
                              << "New height: " << window.getSize().y << '\n';
                    break;
                case sf::Event::KeyPressed:
                    std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                    break;
                default:
                    break;
            }
        }
        //using namespace std::chrono_literals;
        //std::this_thread::sleep_for(1000ms);

        window.clear();
        this->draw();
        window.display();
    }
}

ResourceManager* Game::getResourceManagerPtr() noexcept {
    return &resourceManager;
}

SceneManager* Game::getSceneManagerPtr() noexcept {
    return &sceneManager;
}

std::ostream& operator<< (std::ostream& os, const Game& game) {
    os << game.details << '\n';
    return os;
}

void Game::draw() {
    for(const auto &spritePair : this->sceneManager.sprites)
        window.draw(spritePair.second);
}

sf::Vector2<unsigned int> Game::getScreenSize() const {
    return window.getSize();
}

void Game::addPlayer(Player *playerPtr) {
    this->players.pushbackElement(playerPtr);
}