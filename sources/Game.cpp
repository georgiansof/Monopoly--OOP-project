#include "../headers/Game.hpp"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <random>
#include <regex>
#include "../headers/external/json.hpp"
#include "../constants.hpp"
#include "../headers/DataStructures/CustomExceptions.hpp"

using json = nlohmann::json;
using namespace sf;
using namespace std;

const std::string Globals::bankCStr = "bank";

void Game::AwaitHandshakeAsync(ConnectionToClient *context) {
    context->AwaitHandshake();
    std::cout<< "Port " << context->getPort()<< " connected to " << context->getPeerName() << '\n';

    dynamic_cast<Label*>
        (Game::getInstancePtr()->
            uiManager.elements.
                find("mainmenu_playersConnected")->second)
                    ->appendText(context->getPeerName()
                                    + ":" + to_string(context->getPort())
                                    + "\n");
}

void Game::connectToServer(const std::string& ip, int port, std::string _hostname) {
    std::cout << ip << ' ' << port << '\n';

    connectionToServer = new ConnectionToServer(ip, port, std::move(_hostname));
    //srv->Send("Client closing connection\n");

    //delete srv;
}

void Game::waitForClients(int startPort, int numberOfPlayers) {
    std::cout << "Server up\n\n";
    for(int i = 0; i < numberOfPlayers; ++i) {
        std::cout << "Port " << startPort + Connection::getConnectionCount() << " listening \n";
        connectionsToClients.push_back(new ConnectionToClient(startPort + Connection::getConnectionCount()));
    }

    std::cout<<'\n';

    std::vector<std::thread*> threads;
    for(int i = 0; i < numberOfPlayers; ++i)
        threads.push_back(new std::thread(Game::AwaitHandshakeAsync, connectionsToClients[i]));

    for(auto thread : threads) {
        thread->join();
        delete thread;
    }

    threads.clear();
    std::cout<<'\n';

    std::string playerDetails(this->hostname);
    for(int i = 0; i < numberOfPlayers; ++i) {
        playerDetails += "\n" + connectionsToClients[i]->getPeerName();
    }

    for(int i = 0; i < numberOfPlayers; ++i) {
        connectionsToClients[i]->Send(std::string(ALL_CONNECTED_MSG) + "\n" + playerDetails);
        std::cout << "Message sent to " << connectionsToClients[i]->getPeerName() << ':' << connectionsToClients[i]->getPort() << '\n';
    }

    std::cout<<"All players connected.\n";
    this->destroyMainMenuUI();
    this->showBoard(playerDetails);
    this->window.setTitle(std::string("MonOOPoly (role SERVER) playing as ") + hostname + " colored " + hostColorName);
    for(auto connection : connectionsToClients)
        (new thread([this, connection]() {
            this->serverListenToClient(connection);
        }))->detach();

    /*for(int i = 0; i < numberOfPlayers; ++i)
        std::cout << connectionsToClients[i]->Receive();

    std::cout << "Server shutting down\n\n";
    for(auto &conn : connectionsToClients)
        delete conn;
    connectionsToClients.clear();*/
}

void Game::serverListenToClient(ConnectionToClient *connection) {
    std::string recv = connection->Receive(NO_TIMEOUT);

    auto thrd = new thread([this, recv, connection]() {
        this->eventServerReceivedInput(recv, connection);
    });

    (new thread([this, connection]() {
        this->serverListenToClient(connection);
    }))->detach(); /// loop the listening without filling the stack

    thrd->join(); /// async, but avoiding thread explosion
}

void Game::promptConnectionDetails() {
    TextEntry *namete = dynamic_cast<TextEntry*>
    (uiManager.elements.find("mainmenu_nameEntry")->second);
    Label *namelbl = dynamic_cast<Label*>
    (uiManager.elements.find("mainmenu_nameLabel")->second);
    TextEntry *ipte = dynamic_cast<TextEntry*>
            (uiManager.elements.find("mainmenu_ipEntry")->second);
    Label *iplbl = dynamic_cast<Label*>
            (uiManager.elements.find("mainmenu_ipLabel")->second);
    TextEntry *portte = dynamic_cast<TextEntry*>
            (uiManager.elements.find("mainmenu_portEntry")->second);
    Label *portlbl = dynamic_cast<Label*>
            (uiManager.elements.find("mainmenu_portLabel")->second);

    ipte->setText("");
    portte->setText("");
    switch(hostType) {
        case SERVER:
            namete->setText("SERVER");
            ipte->setText("50000");
            portte->setText("3");
            iplbl->setText("Start port (min 49152, max 65535)");
            ipte->setMaxLength(5);
            ipte->setCharType(TextEntry::chrType::NUMBERS);
            portlbl->setText("Player count (min 2, max 8)");
            portte->setMaxLength(1);
            portte->setCharType(TextEntry::chrType::NUMBERS);
            break;
        case CLIENT:
            namete->setText("CLIENT");
            ipte->setText("127.0.0.1");
            portte->setText("50000");
            iplbl->setText("Server IP");
            portlbl->setText("Communication Port");
            ipte->setMaxLength(15);
            ipte->setCharType(
                TextEntry::chrType::NUMBERS | TextEntry::chrType::DOT);
            portte->setMaxLength(5);
            portte->setCharType(TextEntry::chrType::NUMBERS);
            break;
        default:
            throw SwitchCaseNotCovered();
    }

    iplbl->unhide();
    ipte->unhide();
    portlbl->unhide();
    portte->unhide();
    namete->unhide();
    namelbl->unhide();

    Button *backChooseHost = dynamic_cast<Button*>
            (uiManager.elements.find("mainmenu_back_choose")->second);

    Button *submitConnection = dynamic_cast<Button*>
            (uiManager.elements.find("mainmenu_submit_connection")->second);

    backChooseHost->unhide();
    submitConnection->unhide();
}

void Game::constructMainMenuUI() {
    auto nameEntry = new TextEntry({0.2,0.15},
                                 this->coordinateToPercentage(150.0f, Game::axis::X),
                                 15,
                                 TextEntry::chrType::LETTERS | TextEntry::chrType::NUMBERS,
                                 sf::Color::Blue,
                                 3.0f,
                                 sf::Color::Red,
                                 FONTSIZE_DEFAULT,
                                 sf::Color::Yellow,
                                 sf::Text::Style::Regular,
                                 resourceManager.getFont("arial"));
    auto nameLabel = new Label("Name (Unique!)",
                             *nameEntry,
                             sf::Color(COLOR_ORANGE),
                             10,
                             FONTSIZE_DEFAULT,
                             sf::Color(sf::Color::White),
                             sf::Text::Style::Bold);
    auto chooseServerButton =
            new Button("Server",
                       {0.2, 0.475},
                       {0.2, 0.05},
                       sf::Color::White,
                       sf::Color::Blue,
                       OUTLINE_THICKNESS_DEFAULT,
                       sf::Color::Black,
                       sf::Text::Style::Regular,
                       FONTSIZE_DEFAULT + 10,
                       &Game::mainMenuServerButtonAction);

    auto chooseClientButton =
            new Button("Client",
                       {0.6, 0.475},
                       {0.2, 0.05},
                       sf::Color::White,
                       sf::Color::Blue,
                       OUTLINE_THICKNESS_DEFAULT,
                       sf::Color::Black,
                       sf::Text::Style::Regular,
                       FONTSIZE_DEFAULT + 10,
                       &Game::mainMenuClientButtonAction);

    auto ipEntry = new TextEntry({0.2,0.3},
                 this->coordinateToPercentage(150.0f, Game::axis::X),
                 15,
                 TextEntry::NUMBERS,
                 sf::Color::Blue,
                 3.0f,
                 sf::Color::Red,
                 FONTSIZE_DEFAULT,
                 sf::Color::Yellow,
                 sf::Text::Style::Regular,
                 resourceManager.getFont("arial"));
    auto ipLabel = new Label("IP",
                              *ipEntry,
                              sf::Color::Green,
                              10,
                              FONTSIZE_DEFAULT,
                              sf::Color(COLOR_PURPLE),
                              sf::Text::Style::Bold);
    
    auto portEntry = new TextEntry({0.2,0.5},
                                  this->coordinateToPercentage(150.0f, Game::axis::X),
                                  5,
                                  TextEntry::NUMBERS,
                                  sf::Color::Blue,
                                  3.0f,
                                  sf::Color::Red,
                                  FONTSIZE_DEFAULT,
                                  sf::Color::Yellow,
                                  sf::Text::Style::Regular,
                                  resourceManager.getFont("arial"));
    auto portLabel = new Label("Port",
                                *portEntry,
                                sf::Color::Blue,
                                10,
                                FONTSIZE_DEFAULT,
                                sf::Color::Yellow,
                                sf::Text::Style::Bold);

    auto backChooseHost =
            new Button("Back",
                       {0.6, 0.5},
                       {0.2, 0.05},
                       sf::Color::White,
                       sf::Color::Blue,
                       OUTLINE_THICKNESS_DEFAULT,
                       sf::Color::Black,
                       sf::Text::Style::Regular,
                       FONTSIZE_DEFAULT + 10,
                       &Game::mainMenuBackButtonAction);
    auto submitConnectionDetails =
            new Button("Submit",
                       {0.6, 0.6},
                       {0.2, 0.05},
                       sf::Color::White,
                       sf::Color::Blue,
                       OUTLINE_THICKNESS_DEFAULT,
                       sf::Color::Black,
                       sf::Text::Style::Regular,
                       FONTSIZE_DEFAULT + 10,
                       &Game::mainMenuSubmitButtonAction);

    auto errorMessage = new Label("DEBUGMSG",
                                  {0.2, 0.9},
                                  sf::Color::Red,
                                  10,
                                  FONTSIZE_DEFAULT,
                                  sf::Color::White,
                                  sf::Text::Style::Bold);

    auto playersConnectedLabel = new Label(
            "Players connected: \n",
            {0.3, 0.15});

    auto clientWaitingLabel = new Label(
            "", /// set later
            {0.3, 0.15});

    uiManager.addElement("mainmenu_ipEntry",ipEntry);
    uiManager.addElement("mainmenu_ipLabel",ipLabel);
    uiManager.addElement("mainmenu_portEntry", portEntry);
    uiManager.addElement("mainmenu_portLabel", portLabel);
    uiManager.addElement("mainmenu_choose_client", chooseClientButton);
    uiManager.addElement("mainmenu_choose_server", chooseServerButton);
    
    uiManager.addElement("mainmenu_back_choose", backChooseHost);
    uiManager.addElement("mainmenu_submit_connection", submitConnectionDetails);
    uiManager.addElement("mainmenu_error_message", errorMessage);
    uiManager.addElement("mainmenu_nameEntry", nameEntry);
    uiManager.addElement("mainmenu_nameLabel", nameLabel);
    uiManager.addElement("mainmenu_playersConnected", playersConnectedLabel);

    uiManager.addElement("mainmenu_clientWaiting", clientWaitingLabel);
    nameEntry->hide();
    nameLabel->hide();
    ipEntry->hide();
    ipLabel->hide();
    portEntry->hide();
    portLabel->hide();
    backChooseHost->hide();
    submitConnectionDetails->hide();
    errorMessage->hide();
    playersConnectedLabel->hide();
    clientWaitingLabel->hide();
}

void Game::mainMenuSubmitButtonAction() {
    TextEntry *namete = dynamic_cast<TextEntry*>
    (Game::getInstancePtr()->uiManager.elements.find("mainmenu_nameEntry")->second);
    Label *namelbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements.find("mainmenu_nameLabel")->second);

    TextEntry *ipte = dynamic_cast<TextEntry*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_ipEntry")->second);
    Label *iplbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_ipLabel")->second);
    TextEntry *portte = dynamic_cast<TextEntry*>
    (Game::getInstancePtr()->uiManager.elements.find("mainmenu_portEntry")->second);
    Label *portlbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_portLabel")->second);
    Button *backChooseHost = dynamic_cast<Button*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_back_choose")->second);

    Button *submitConnection = dynamic_cast<Button*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_submit_connection")->second);

    Label *errorLbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_error_message")->second);

    Label *playersConnectedLbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_playersConnected")->second);

    Label *clientWaitingLbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_clientWaiting")->second);

    if(ipte->getText().empty() || portte->getText().empty() || namete->getText().empty()) {
        errorLbl->setText("All entries are mandatory.");
        errorLbl->showForSeconds(ERROR_SHOWTIME);
        return;
    }

    std::string name = namete->getText();

    /// client
    std::string ip;
    int port;

    /// server
    int startPort;
    int numberOfPlayers;


    switch(Game::getInstancePtr()->hostType) {
        case SERVER: {
            startPort = std::stoi(ipte->getText());
            numberOfPlayers = std::stoi(portte->getText());
            if(startPort < DYNAMIC_PORT_RANGE_MIN || startPort > DYNAMIC_PORT_RANGE_MAX) {
                errorLbl->setText("Incorrect port. Make sure port is range [49152 - 65535] (Dynamic/private port range).");
                errorLbl->showForSeconds(ERROR_SHOWTIME);
                return;
            }
            if(numberOfPlayers < 2 || numberOfPlayers > 8) {
                errorLbl->setText("There can be at least two players and at most eight.");
                errorLbl->showForSeconds(ERROR_SHOWTIME);
                return;
            }
            playersConnectedLbl->unhide();
            break;
        }
        case CLIENT: {
            ip = ipte->getText();
            port = std::stoi(portte->getText());
            std::regex patternIP(R"(^((((2[0-4][0-9])|(25[0-5])|(1[0-9]{1,2})|[0-9])\.){3}((2[0-4][0-9])|(25[0-5])|(1[0-9]{1,2})|[0-9]))$)");

            if(!std::regex_match(ip, patternIP)) {
                errorLbl->setText("IP given doesn't match ipv4 pattern");
                errorLbl->showForSeconds(ERROR_SHOWTIME);
                return;
            }

            if(port < DYNAMIC_PORT_RANGE_MIN || port > DYNAMIC_PORT_RANGE_MAX) {
                errorLbl->setText("Incorrect port. Make sure port is range [49152 - 65535] (Dynamic/private port range).");
                errorLbl->showForSeconds(ERROR_SHOWTIME);
                return;
            }
            clientWaitingLbl->setText("Trying to connect to server.");
            clientWaitingLbl->unhide();
            break;
        }
        default:
            throw SwitchCaseNotCovered();
    }

    namete->hide();
    namelbl->hide();
    ipte->hide();
    iplbl->hide();
    portte->hide();
    portlbl->hide();
    backChooseHost->hide();
    submitConnection->hide();
    errorLbl->hide();

    auto game = Game::getInstancePtr();

    game->hostname = name;

    if(game->hostType == CLIENT) {
        game->connectToServer(ip, port, name);
        clientWaitingLbl->setText("Waiting for everyone to connect.");
    }

    if(game->hostType == SERVER)
        game->waitForClients(startPort, numberOfPlayers - 1);
}

void Game::mainMenuBackButtonAction() {
    TextEntry *namete = dynamic_cast<TextEntry*>
            (Game::getInstancePtr()->uiManager.elements.find("mainmenu_nameEntry")->second);
    Label *namelbl = dynamic_cast<Label*>
            (Game::getInstancePtr()->uiManager.elements.find("mainmenu_nameLabel")->second);
    TextEntry *ipte = dynamic_cast<TextEntry*>
            (Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_ipEntry")->second);
    Label *iplbl = dynamic_cast<Label*>
            (Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_ipLabel")->second);
    TextEntry *portte = dynamic_cast<TextEntry*>
            (Game::getInstancePtr()->uiManager.elements.find("mainmenu_portEntry")->second);
    Label *portlbl = dynamic_cast<Label*>
            (Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_portLabel")->second);
    Button *backChooseHost = dynamic_cast<Button*>
            (Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_back_choose")->second);
    Button *submitConnection = dynamic_cast<Button*>
            (Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_submit_connection")->second);
    Label *errorLbl = dynamic_cast<Label*>
    (Game::getInstancePtr()->uiManager.elements
                    .find("mainmenu_error_message")->second);

    namete->hide();
    namelbl->hide();
    ipte->hide();
    iplbl->hide();
    portte->hide();
    portlbl->hide();
    backChooseHost->hide();
    submitConnection->hide();
    errorLbl->hide();

    auto clientButton =
            Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_choose_client")->second;
    auto serverButton =
            Game::getInstancePtr()->uiManager.elements
            .find("mainmenu_choose_server")->second;

    clientButton->unhide();
    serverButton->unhide();
}

void Game::mainMenuClientButtonAction() {
    auto clientButtonPair =
            Game::getInstancePtr()->uiManager.elements.find("mainmenu_choose_client");
    auto serverButtonPair =
            Game::getInstancePtr()->uiManager.elements.find("mainmenu_choose_server");
    /// downcast will be valid

    Game::getInstancePtr()->hostType = CLIENT;
    clientButtonPair->second->hide();
    serverButtonPair->second->hide();
    Game::getInstancePtr()->promptConnectionDetails();
}

void Game::mainMenuServerButtonAction() {
    auto clientButtonPair =
            Game::getInstancePtr()->uiManager.elements.find("mainmenu_choose_client");
    auto serverButtonPair =
            Game::getInstancePtr()->uiManager.elements.find("mainmenu_choose_server");

    Game::getInstancePtr()->hostType = SERVER;
    clientButtonPair->second->hide();
    serverButtonPair->second->hide();
    Game::getInstancePtr()->promptConnectionDetails();
}

void Game::destroyMainMenuUI() {
    for(auto it = uiManager.elements.begin(); it != uiManager.elements.end();)
        if(it->first.starts_with("mainmenu_")) {
            delete it->second;
            it = uiManager.elements.erase(it);
        }
        else
            ++it;
}

CircularList<Player*>::iterator& Game::getCurrentPlayerIterator() {
    return this->currentPlayerIterator;
}

[[maybe_unused]] Game::host_type Game::getHostType() const noexcept {
    return this->hostType;
}

[[maybe_unused]] ConnectionToServer* Game::getConnectionToServer() {
    return this->connectionToServer;
}

[[maybe_unused]] vector<ConnectionToClient*>& Game::getConnectionsToClients() {
    return this->connectionsToClients;
}

Game::Game() {
    Game::instance = nullptr;
    this->details = "MonOOPoly game by georgiansof";
}

[[maybe_unused]] const sf::Font& Game::getDefaultFont() const {
    if(defaultFont)
        return *defaultFont;
    else
        throw AssetNotFoundException("default font");
}

Game* Game::getInstancePtr() {
    if(Game::instance != nullptr)
        return Game::instance;
    else {
        Game::instance = new Game;
        instance->window.setKeyRepeatEnabled(Globals::doesKeyPressedRepeat());
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
    window.create(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "MonOOPoly", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->windowSize = {DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT};
    window.setVerticalSyncEnabled(true);
    ///window.setFramerateLimit(60);
}

void Game::loop() {
        while(window.isOpen()) {
            sf::Event e{};
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::Resized:
                        eventWindowResized(windowSize);
                        windowSize = window.getSize();
                        break;
                    case sf::Event::KeyPressed:
                            this->eventKeyPressed(e.key.code);
                        break;
                    case sf::Event::KeyReleased:
                            Game::eventKeyReleased(e.key.code);
                        break;
                    case sf::Event::MouseButtonPressed:
                            this->eventMousePressed(e.mouseButton.button, sf::Mouse::getPosition(this->window));
                        break;
                    case sf::Event::TextEntered:
                            this->eventTextEntered(static_cast<char>(e.text.unicode));
                    default:
                        break;
                }
            }
            //using namespace std::chrono_literals;
            //std::this_thread::sleep_for(1000ms);

            window.clear();
            this->verifyTemporarilyVisibleUI();
            this->draw();
            window.display();
        }
}

void Game::verifyTemporarilyVisibleUI() {
    for(auto& uiElemPair : uiManager.elements)
        if(uiElemPair.second->isTimerOn()) {
            auto timestamp = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsedTime = (timestamp - uiElemPair.second->getTimerStart());
            float elapsedTimeFloat = elapsedTime.count();
            float maxTimeFloat = uiElemPair.second->getVisibleTime();
            if(elapsedTimeFloat >= maxTimeFloat)
                uiElemPair.second->hide();
        }
}

ResourceManager* Game::getResourceManagerPtr() noexcept {
    return &resourceManager;
}

[[maybe_unused]] SceneManager* Game::getSceneManagerPtr() noexcept {
    return &sceneManager;
}

UIManager* Game::getuiManagerPtr() noexcept {
    return &uiManager;
}

std::ostream& operator<< (std::ostream& os, Game& game) {
    os << game.details << '\n';
    os << "Players: ";
    auto it = game.players.begin();
    do {
        if(it != game.players.begin())
            os << ", ";
        os << (*it)->getName();
        ++it;
    }
    while(it != game.players.begin());
    os << ";\n";

    return os;
}

void Game::draw() {
    for(const auto &spritePair : this->sceneManager.sprites)
        window.draw(spritePair.second);
    for(const auto &shapePair : this->sceneManager.shapePointers)
        window.draw(*shapePair.second);

    if(!uiManager.dice1->isInvisible())
        window.draw(uiManager.dice1->getShape());
    if(!uiManager.dice2->isInvisible())
        window.draw(uiManager.dice2->getShape());

    for(const auto &uiElement : this->uiManager.elements)
        if(!uiElement.second->isInvisible())
            uiElement.second->draw(&window);
}

sf::Vector2<unsigned int> Game::getWindowSize() const {
    return window.getSize();
}

bool Game::isDiceRollingLocked() const {
    return lockDiceRoll;
}

void Game::addTiles() {
    std::ifstream propertiesFile("../data/properties.json");
    json propertiesJSON = json::parse(propertiesFile);

    for(int i = 0; i < 40; ++i)
        switch(i) {
        case 0:
            board.AddTile(new ParkTile(i, ParkTile::Type::START));
            break;
        case 2:
        case 17:
        case 33:
            board.AddTile(new ChanceTile(ChanceTile::Type::COMMUNITY, i));
            break;
        case 7:
        case 22:
        case 36:
            board.AddTile(new ChanceTile(ChanceTile::Type::SURPRISE, i));
            break;
        case 10:
            board.AddTile(new Jail());
            break;
        case 20:
            board.AddTile(new ParkTile(i, ParkTile::Type::FREE_PARKING));
            break;
        case 30:
            board.AddTile(new ParkTile(i, ParkTile::Type::GO_TO_JAIL));
            break;
        case 4: {
            uint32_t amount = 0;
            std::ifstream taxfile("../data/taxes.json");
            json data = json::parse(taxfile);
            for(const auto& entry : data)
                if(entry["type"] == "income") {
                    amount = entry["amount"];
                    break;
                }
            board.AddTile(new TaxTile(TaxTile::Type::INCOME, i, amount));
            break;
        }
        case 38: {
            uint32_t amount = 0;
            std::ifstream taxfile("../data/taxes.json");
            json data = json::parse(taxfile);
            for(const auto& entry : data)
                if(entry["type"] == "luxury") {
                    amount = entry["amount"];
                    break;
                }
            board.AddTile(new TaxTile(TaxTile::Type::LUXURY, i, amount));
            taxfile.close();
            break;
        }
        case 12: {/// electric factory
            for(const auto &property : propertiesJSON)
                if(property.contains("factory_type") && property["factory_type"] == "electricity") {
                    board.AddTile(new Factory(Factory::Type::ELECTRICITY, i, property["price"], property["one_multiplier"], property["two_multiplier"]));
                    break;
                }
            break;
        }
        case 28: { /// water factory
            for(const auto &property : propertiesJSON)
                if(property.contains("factory_type") && property["factory_type"] == "water") {
                    board.AddTile(new Factory(Factory::Type::WATER, i, property["price"], property["one_multiplier"], property["two_multiplier"]));
                    break;
                }
            break;
        }
        case 5:
        case 15:
        case 25:
        case 35: { /// train
            for(const auto &property : propertiesJSON)
                if(property.contains("train_index") && property["train_index"] == i/10 + 1) {
                    uint32_t fees[5];
                    fees[1] = property["one_fee"];
                    fees[2] = property["two_fee"];
                    fees[3] = property["three_fee"];
                    fees[4] = property["four_fee"];
                    std::string name = property["name"];
                    uint8_t train_index = property["train_index"];
                    uint32_t price = property["price"];

                    board.AddTile(new TrainStation(name, train_index, price , fees));
                    break;
                }
            break;
        }
        default: { /// property
            for(const auto &property : propertiesJSON)
                if(property.contains("position") && property["position"] == i) {
                    uint32_t rent[6] = {property["zero_rent"],
                                        property["one_rent"],
                                        property["two_rent"],
                                        property["three_rent"],
                                        property["four_rent"],
                                        property["hotel_rent"]};
                    uint32_t price = property["price"];
                    std::string name = property["name"];
                    sf::Color color;
                    if(i < 5)
                        color = sf::Color(PROPERTY_BROWN);
                    else
                        if(i < 10)
                            color = sf::Color(PROPERTY_LIGHT_BLUE);
                        else
                            if(i < 15)
                                color = sf::Color(PROPERTY_PINK);
                            else
                                if(i < 20)
                                    color = sf::Color(PROPERTY_ORANGE);
                                else
                                    if(i < 25)
                                        color = sf::Color(PROPERTY_RED);
                                    else
                                        if(i < 30)
                                            color = sf::Color(PROPERTY_YELLOW);
                                        else
                                            if(i < 35)
                                                color = sf::Color(PROPERTY_GREEN);
                                            else
                                                color = sf::Color(PROPERTY_DARK_BLUE);
                    board.AddTile(new Neighborhood(name, color, i, price, rent));
                    break;
                }
        }
        }
    propertiesFile.close();
    //std::cout << board.getTileCount() << '\n';
    if(board.getTileCount() != 40)
        throw InsufficientTilesException(board.getTileCount());
}

void Game::addPlayer(Player *playerPtr) {
    if(this->players.size() >= 8)
        throw PlayerCountException(playerPtr->getName());

    this->players.push_back(playerPtr);
    if(players.size() == 1) /// first inserted player
        this->currentPlayerIterator = players.begin();

    auto playerPositionPair = board.getTile(0).addPlayer(playerPtr);

    sf::Vector2<float> playerPiecePosition = playerPositionPair.first;
    playerPtr->indexInsideTile = playerPositionPair.second;

    float screenX = (float)this->getWindowSize().x;
    float screenY = (float)this->getWindowSize().y;

    playerPiecePosition.x *= screenX;
    playerPiecePosition.y *= screenY;

    auto playerPieceRadius = (float) std::min(screenX, screenY) / 48 / 2;
    auto playerPieceShapePtr = new sf::CircleShape();
    playerPieceShapePtr->setRadius(playerPieceRadius);
    playerPieceShapePtr->setPosition(playerPiecePosition);
    playerPieceShapePtr->setFillColor(playerPtr->getColor());
    playerPieceShapePtr->setOutlineThickness(1.5);
    playerPieceShapePtr->setOutlineColor(sf::Color::Black);
    playerPtr->boardPieceShapePtr = playerPieceShapePtr;
    this->sceneManager.addShape(std::string("player_") + std::string(playerPtr->getName()), playerPieceShapePtr);
    /*
    sf::Vector2<int> playerPieceSize ((int)this->getScreenSize().x / 36, (int)this->getScreenSize().y / 36);
    sf::Rect<int> playerRect(playerPiecePosition,playerPieceSize);

    auto playerPieceSpritePtr = new sf::Sprite;
    playerPieceSpritePtr->setColor(playerPtr->getColor());
    playerPieceSpritePtr->setTextureRect(playerRect);
    playerPieceSpritePtr->setTexture(this->resourceManager.getTexture("blank"));
    playerPieceSpritePtr->setPosition(playerPiecePositionFloat);

    this->sceneManager.addSprite(std::string("player_") + std::string(playerPtr->getName()), playerPieceSpritePtr);
     */
}

std::pair<uint8_t,uint8_t> Game::diceRoll() {
    //srand(time(nullptr));
    //return std::pair<uint8_t,uint8_t>(rand() % 6 + 1, rand() % 6 + 1);
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<uint8_t> distribution(1,6);
    uint8_t dice1 = distribution(gen);
    uint8_t dice2 = distribution(gen);
    return {dice1,dice2};
}

sf::Vector2f Game::coordinatesToPercentage(sf::Vector2f coord) const {
    sf::Vector2f screenSize = Vector2f(this->getWindowSize());
    return {coord.x / screenSize.x, coord.y / screenSize.y};
}

sf::Vector2f Game::percentageToCoordinates(sf::Vector2f perc) const {
    sf::Vector2f screenSize = Vector2f(this->getWindowSize());
    return {perc.x * screenSize.x, perc.y * screenSize.y};
}

float Game::coordinateToPercentage(float coord, Game::axis which) const {
    if(which == Game::axis::X)
        return coord / (float)this->getWindowSize().x;
    else
        return coord / (float)this->getWindowSize().y;
}

[[maybe_unused]] float Game::percentageToCoordinate(float perc, Game::axis which) const {
    if(which == Game::axis::X)
        return perc * (float)this->getWindowSize().x;
    else
        return perc * (float)this->getWindowSize().y;
}

Game::~Game() {
    delete initConnectThread;
}

void Game::clientListenToServer() {
    std::string recv = connectionToServer->Receive(NO_TIMEOUT);

    auto thrd = new thread([this,recv]() -> void {
        this->eventClientReceivedInput(recv);
    });

    (new thread([this]() {
        this->clientListenToServer();
    }))->detach(); /// recursivity without stack fill

    thrd->join(); /// asynchronous thread creation to prevent deadlocks
}

int handleFatalException(exception &e) {
    std::cerr << e.what();
    auto fatalExceptCast = dynamic_cast<FatalException*>(&e);
    if(fatalExceptCast == nullptr)
        return UNHANDLED_ERROR_CODE;
    else
        return fatalExceptCast->getExitCode();
}

void Game::extractPlayerNames(std::vector<std::string> &playerNames, const std::string& playerDetails) {
    istringstream iss(playerDetails);
    std::string line;
    while(std::getline(iss, line, '\n')) {
        std::cout << line <<'\n';
        playerNames.emplace_back(line);
    }
}

void Game::setFactoryWaitingDiceRoll(bool val) {
    this->factoryWaitingDiceRoll = val;
}

void Game::showBoard(const std::string& playerDetails) {
    try {
        sceneManager.addSprite("board", resourceManager.getTexture("board"));
        sceneManager.addSound("coin flip", resourceManager.getAudio("coin flip"));
        /// scale board to screen
        Sprite& boardSpriteRef = sceneManager.getSpriteReference("board");
        boardSpriteRef.setScale((float) getWindowSize().x / boardSpriteRef.getLocalBounds().width,
                       (float) getWindowSize().y / boardSpriteRef.getLocalBounds().height);
        uiManager.dice1->unhide();
        uiManager.dice2->unhide();
    }
    catch(exception &e) {
        exit(handleFatalException(e));
    }

    /// ADD TILES

    try {this->addTiles();}
    catch (exception &e) {
        exit(handleFatalException(e));
    }
    ///  ADD PLAYERS
    try {
        vector<sf::Color> colors {Color::Black,
                                  Color::Yellow,
                                  Color::Green,
                                  Color::Red,
                                  Color::Magenta,
                                  Color::Blue,
                                  Color::Cyan,
                                  Color::White};

        vector<std::string> playerNames;
        extractPlayerNames(playerNames, playerDetails);
        for(int i = 0; i < (int)playerNames.size(); ++i) {
            auto plyr = new Player(playerNames[i], colors[i]);
            this->addPlayer(plyr);
            if(plyr->getName() == hostname)
                hostColorName = plyr->getColorName();
        }
    }
    catch(std::exception &e) {
        if(dynamic_cast<FatalException*>(&e) == nullptr)
            std::cerr << e.what();
        else
            handleFatalException(e);
    }

    auto whoAtTurnLabel = new Label(
            (*currentPlayerIterator)->getName() + "'s turn.",
            {0.5, 0.3},
            sf::Color(COLOR_PURPLE),
            5.0f,
            FONTSIZE_DEFAULT + 10,
            sf::Color::Yellow,
            sf::Text::Style::Italic
    );

    auto hostMoney = new Label(
                "Your money: " + to_string(getPlayerByName(hostname)->getAvailableMoney()) + "M",
                {0.5f, 0.25f},
                sf::Color(COLOR_ORANGE),
                5.0f,
                FONTSIZE_DEFAULT + 10
            );
    uiManager.addElement("whosTurnLabel", whoAtTurnLabel);
    uiManager.addElement("host_money", hostMoney);
}


bool Game::isNameTaken(const std::string &name) const {
    if(name == this->hostname)
        return true;

    bool theOneAddedFound = false;
    for(auto connection : connectionsToClients)
        if(connection->getPeerName() == name) {
            if(!theOneAddedFound)
                theOneAddedFound = true;
            else
                return true;
        }
    return false;
}

Board *Game::getBoardPtr() noexcept {
    return &this->board;
}

const std::string &Game::getHostName() const noexcept {
    return this->hostname;
}

void Game::broadcastToClients(const std::string& msg, std::vector<std::string> except) {
    for(auto connection : connectionsToClients)
        if(std::find(except.begin(), except.end(), connection->getPeerName()) == except.end())
            connection->Send(msg);
}

void Game::broadcastFromClient(const std::string &msg) {
    connectionToServer->Send("broadcast " + msg);
}

void Game::broadcast(const std::string& msg) {
    if(this->hostType == SERVER)
        broadcastToClients(msg);
    else
        broadcastFromClient(msg);
}

void Game::makeMove(int dice1, int dice2) {
    Player *currentPlayer = *currentPlayerIterator;
    Label *lbl = dynamic_cast<Label*> (this->uiManager.getElement("whosTurnLabel"));

    if(timesRolledDouble == 2 && dice1 == dice2) {
        currentPlayer->sendToJail();
        timesRolledDouble = 0;
        ++currentPlayerIterator;
        return;
    }
    currentPlayer->moveSpaces(dice1+dice2);
    lockDiceRoll = true;
    board.getTile(currentPlayer->getBoardPosition()).onVisit(currentPlayer);
    lockDiceRoll = false;
    if(dice1 == dice2)
        ++timesRolledDouble;
    else {
        timesRolledDouble = 0;
        ++currentPlayerIterator;
    }

    if(dice1 != dice2)
        lbl->setText((*currentPlayerIterator)->getName() + "'s turn.");
}

void Game::submitLicitation() {
    Game *game = Game::getInstancePtr();
    auto *entry = dynamic_cast<TextEntry*>
                                (game->uiManager.getElement("bid_entry"));
    if(stoul(entry->getText()) > game->getPlayerByName(game->hostname)->getAvailableMoney()) {
        cout << "You don't have enough money!\n";
        return;
    }

    game->broadcast("bid " + game->hostname + " " + entry->getText());
    game->eventClientReceivedInput("bid " + game->hostname + " " + entry->getText());
    entry->setText("");
}

void Game::propertyLicitation(Property *prop) {
    /// server broadcasts licitation start
    /// the bank offers half the price and if no one raises, the bank keeps it
    /// licitation ends when no one offers for a LICITATION_TIMEOUT constant time
    Game *game = Game::getInstancePtr();
    auto *licitationPriceLabel = new Label(
                "The highest bid is " + to_string(prop->getPrice() / 2) + " from bank.",
                {0.3f, 0.2f},
                sf::Color::Yellow,
                5,
                FONTSIZE_DEFAULT,
                sf::Color::Green
            );
    uiManager.addElement("licitation_price", licitationPriceLabel);
    licitationInCourse = true;
    playerBid bankBid {Globals::getBankStrPtr(), prop->getPrice() / 2};
    highestBid = bankBid;
    if(game->hostType == Game::SERVER) {
        broadcast("licitation start");
        eventClientReceivedInput("licitation start");

        auto start = std::chrono::steady_clock::now();
        std::chrono::duration<float> fsec = std::chrono::steady_clock::now() - start;
        while(fsec.count() < LICITATION_TIMEOUT) {
            if(restartTimer) {
                restartTimer = false;
                start = std::chrono::steady_clock::now();
            }
            fsec = std::chrono::steady_clock::now() - start;
        }

        broadcast("licitation end "
        + ((highestBid.load().playerName == nullptr) ? "bank" : (*highestBid.load().playerName))
        + " "
        + to_string(highestBid.load().price));
        eventClientReceivedInput("licitation end");
    }

    while(licitationInCourse)
        continue;

    Player *winner = getPlayerByName(*highestBid.load().playerName);
    uint32_t winningPrice = highestBid.load().price;

    winner->payToBank(winningPrice);
    winner->addOwnedProperty(prop);
    prop->setOwner(winner);

    licitationPriceLabel->setText("Licitation won by "
                                + *highestBid.load().playerName
                                + " with price "
                                + to_string(highestBid.load().price));

    std::this_thread::sleep_for(std::chrono::seconds(3));

    uiManager.removeElement("licitation_price");
}

bool Game::isFactoryWaitingDiceRoll() const {
    return factoryWaitingDiceRoll;
}

Player* Game::getPlayerByName(const std::string &name) {
    auto it = currentPlayerIterator;
    do {
        if((*it)->getName() == name)
            return *it;
        ++it;
    }
    while(it != currentPlayerIterator);
    return nullptr;
}

void Game::updateMoneyLabel() {
    uiManager.updateMoneyLabel();
}