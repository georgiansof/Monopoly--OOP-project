#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "external/SDL2/SDL.h"
#include "external/SDL2/SDL_net.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#include <chrono>
#include <thread>
#include <vector>
#include <cstring>

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

#include "Networking/Connection.hpp"

class Game {
public:
    enum axis {X,Y};
    enum host_type {UNDEFINED = 0, CLIENT = 1, SERVER = 2};
private:
    Game();
    ~Game();
    static Game* instance;

    std::string details;
    std::string hostname;
    std::string hostColorName;
    sf::RenderWindow window;
    sf::Vector2u windowSize;
    uint32_t sizeMultiplierSinceStartX = 1;
    uint32_t sizeMultiplierSinceStartY = 1;
    host_type hostType = UNDEFINED;

    ResourceManager resourceManager;
    SceneManager sceneManager;
    UIManager uiManager;

    Board board;
    CircularList<Player*> players;
    CircularList<Player*>::iterator currentPlayerIterator;

    sf::Font *defaultFont = nullptr;

    std::vector<ConnectionToClient*> connectionsToClients;
    ConnectionToServer *connectionToServer = nullptr;
    std::thread *initConnectThread = nullptr;

    int timesRolledDouble = 0;

    void connectToServer(std::string ip, int port, std::string hostname);
    void waitForClients(int startPort, int numberOfPlayers);
    static void AwaitHandshakeAsync(ConnectionToClient *context);
    static void extractPlayerNames(std::vector<std::string> &playerNames, const std::string& playerDetails);
    void serverListenToClient(ConnectionToClient* connection);
    void clientListenToServer();
    void broadcastToClients(const std::string& msg, std::vector<std::string> except = std::vector<std::string>());
    void broadcastFromClient(const std::string& msg);

    void makeMove(int dice1, int dice2);
public:
    void broadcast(const std::string& msg);

    ResourceManager* getResourceManagerPtr() noexcept;
    SceneManager* getSceneManagerPtr() noexcept;
    Board* getBoardPtr() noexcept;
    UIManager* getuiManagerPtr() noexcept;
    static Game * getInstancePtr();
    CircularList<Player*>::iterator& getCurrentPlayerIterator();
    host_type getHostType() const noexcept;
    ConnectionToServer* getConnectionToServer();
    std::vector<ConnectionToClient*>& getConnectionsToClients();
    const std::string& getHostName() const noexcept;

    sf::Vector2<unsigned int> getWindowSize() const;
    const sf::Font& getDefaultFont() const;
    static void clearInstance();
    void initWindow();
    void loop();
    void draw();
    friend std::ostream& operator<< (std::ostream& os, Game& game); /// prints game details

    void eventKeyPressed(sf::Keyboard::Key keycode);
    void eventKeyReleased(sf::Keyboard::Key keycode);
    void eventWindowResized(sf::Vector2u windowSizeOld);
    void eventMousePressed(sf::Mouse::Button click, sf::Vector2i position);
    void eventTextEntered(char chr);
    void eventServerReceivedInput(const std::string& input, ConnectionToClient *from);
    void eventClientReceivedInput(const std::string& input);
    void clientEventAllConnected(std::string playerDetails);

    void addTiles();
    void addPlayer(Player *playerPtr);
    bool isNameTaken(const std::string& name) const;

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
    static void mainMenuSubmitButtonAction();

    void showBoard(std::string playerDetails);
};

#endif //OOP_GAME_H
