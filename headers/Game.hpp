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

#include "Managers/ResourceManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/UIManager.hpp"

#include "Player.hpp"
#include "Board.hpp"
#include "UI/UIElement.hpp"

#include "Tiles/BoardTile.hpp"
#include "Tiles/Jail.hpp"
#include "Tiles/Property.hpp"
#include "Tiles/TaxTile.hpp"
#include "Tiles/ParkTile.hpp"
#include "Tiles/ChanceTile.hpp"
#include "Tiles/Neighborhood.hpp"
#include "Tiles/Factory.hpp"
#include "Tiles/TrainStation.hpp"

#include "DataStructures/CircularList.hpp"
#include "DataStructures/CustomExceptions.hpp"

class Game {
public:
    enum axis {X,Y};
    enum host_type {UNDEFINED, CLIENT, SERVER};
private:
    Game();
    ~Game() = default;
    static Game* instance;

    std::string details;
    sf::RenderWindow window;
    host_type hostType = UNDEFINED;

    ResourceManager resourceManager;
    SceneManager sceneManager;
    UIManager uiManager;

    Board board;
    CircularList<Player*> players;
    CircularList<Player*>::iterator currentPlayerIterator;

    sf::Font *defaultFont = nullptr;
public:
    ResourceManager* getResourceManagerPtr() noexcept;
    SceneManager* getSceneManagerPtr() noexcept;
    UIManager* getuiManagerPtr() noexcept;
    static Game * getInstancePtr();
    sf::Vector2<unsigned int> getWindowSize() const;
    const sf::Font& getDefaultFont() const;
    static void clearInstance();
    void initWindow();
    void loop();
    void draw();
    friend std::ostream& operator<< (std::ostream& os, Game& game); /// prints game details

    void eventKeyPressed(sf::Keyboard::Key keycode);
    void eventKeyReleased(sf::Keyboard::Key keycode);
    void eventWindowResized();
    void eventMousePressed(sf::Mouse::Button click, sf::Vector2i position);
    void eventTextEntered(char chr);

    void addTiles();
    void addPlayer(Player *playerPtr);

    static std::pair<uint8_t,uint8_t> diceRoll();
    void nextPlayer();

    sf::Vector2f coordinatesToPercentage(sf::Vector2f coord) const;
    sf::Vector2f percentageToCoordinates(sf::Vector2f perc) const;
    float coordinateToPercentage(float coord, axis which) const;
    float percentageToCoordinate(float perc, axis which) const;

    void verifyTemporarilyVisibleUI();

    void constructMainMenuUI();
    void destroyMainMenuUI();
    void promptConnectionDetails();

    static void mainMenuServerButtonAction();
    static void mainMenuClientButtonAction();
    static void mainMenuBackButtonAction();
};

#endif //OOP_GAME_H
