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
#include <vector>

#include "external/json.hpp" /// https://github.com/nlohmann/json/

#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"
#include "DataStructures/CircularList.hpp"
#include "Board.hpp"

#include "Tiles/BoardTile.hpp"
#include "Tiles/Jail.hpp"
#include "Tiles/Property.hpp"
#include "Tiles/TaxTile.hpp"
#include "Tiles/ParkTile.hpp"
#include "Tiles/ChanceTile.hpp"
#include "Tiles/Neighborhood.hpp"
#include "Tiles/Factory.hpp"
#include "Tiles/TrainStation.hpp"

#include "DataStructures/CustomExceptions.hpp"

class Game {
private:
    Game();
    ~Game() = default;
    static Game* instance;

    std::string details;
    sf::RenderWindow window;
    ResourceManager resourceManager;
    SceneManager sceneManager;

    Board board;
    CircularList<Player*> players;

    CircularList<Player*>::iterator currentPlayerIterator;

public:
    ResourceManager* getResourceManagerPtr() noexcept;
    SceneManager* getSceneManagerPtr() noexcept;
    static Game * getInstancePtr();
    sf::Vector2<unsigned int> getScreenSize() const;
    static void clearInstance();
    void initWindow();
    void loop();
    void draw();
    friend std::ostream& operator<< (std::ostream& os, Game& game); /// prints game details

    void addTiles();
    void addPlayer(Player *playerPtr);

    static std::pair<uint8_t,uint8_t> diceRoll();
    void nextPlayer();
};

#endif //OOP_GAME_H
