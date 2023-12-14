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

void Game::promptConnectionDetails() {
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
            iplbl->setText("Start port (min 49152, max 65535)");
            ipte->setMaxLength(5);
            ipte->setCharType(TextEntry::chrType::NUMBERS);
            portlbl->setText("Player count (min 2, max 8)");
            portte->setMaxLength(1);
            portte->setCharType(TextEntry::chrType::NUMBERS);
            break;
        case CLIENT:
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

    Button *backChooseHost = dynamic_cast<Button*>
            (uiManager.elements.find("mainmenu_back_choose")->second);

    Button *submitConnection = dynamic_cast<Button*>
            (uiManager.elements.find("mainmenu_submit_connection")->second);

    backChooseHost->unhide();
    submitConnection->unhide();
}

void Game::constructMainMenuUI() {
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


    uiManager.addElement("mainmenu_ipEntry",ipEntry);
    uiManager.addElement("mainmenu_ipLabel",ipLabel);
    uiManager.addElement("mainmenu_portEntry", portEntry);
    uiManager.addElement("mainmenu_portLabel", portLabel);
    uiManager.addElement("mainmenu_choose_client", chooseClientButton);
    uiManager.addElement("mainmenu_choose_server", chooseServerButton);
    
    uiManager.addElement("mainmenu_back_choose", backChooseHost);
    uiManager.addElement("mainmenu_submit_connection", submitConnectionDetails);
    uiManager.addElement("mainmenu_error_message", errorMessage);

    ipEntry->hide();
    ipLabel->hide();
    portEntry->hide();
    portLabel->hide();
    backChooseHost->hide();
    submitConnectionDetails->hide();
    errorMessage->hide();
}

void Game::mainMenuSubmitButtonAction() {
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

    if(ipte->getText().empty() || portte->getText().empty()) {
        errorLbl->setText("All entries are mandatory.");
        errorLbl->showForSeconds(ERROR_SHOWTIME);
        return;
    }

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
            break;
        }
        default:
            throw SwitchCaseNotCovered();
    }

    ipte->hide();
    iplbl->hide();
    portte->hide();
    portlbl->hide();
    backChooseHost->hide();
    submitConnection->hide();
    errorLbl->hide();

    if(Game::getInstancePtr()->hostType == CLIENT)
        Game::getInstancePtr()->connectToServer(ip, port);
    if(Game::getInstancePtr()->hostType == SERVER)
        Game::getInstancePtr()->waitForClients(startPort, numberOfPlayers);
}

void Game::mainMenuBackButtonAction() {
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

void Game::eventKeyPressed(sf::Keyboard::Key keycode) {
    for(auto& uiObj : uiManager.elements)
        uiObj.second->onKeyPress(keycode);

    /*if(keycode == Keyboard::Key::Enter) {
        Player *currentPlayer = *currentPlayerIterator;
        cout << currentPlayer->getName() << "'s turn: \n";
        cout << "Position before: " << currentPlayer->getBoardPosition() << '\n';
        pair<uint8_t,uint8_t> dices;
        uint8_t timesRolledDouble = 0;
        int totalMoved = 0;
        do {
            dices = Game::diceRoll();
            if (dices.first == dices.second && timesRolledDouble == 2) {
                timesRolledDouble = 3;
                ///jail player
            }
            else {
                if (dices.first == dices.second)
                    ++timesRolledDouble;
                board.getTile(currentPlayer->getBoardPosition()).removePlayer(currentPlayer->getIndexInsideTile());
                auto updatedPosition = currentPlayer->incrementPosition(dices.first + dices.second);
                totalMoved += (dices.first + dices.second);
                auto newPositionInsideTile = board.getTile(updatedPosition.first).addPlayer(currentPlayer);
                currentPlayer->indexInsideTile = newPositionInsideTile.second;
                newPositionInsideTile.first.x *= (float)this->getWindowSize().x;
                newPositionInsideTile.first.y *= (float)this->getWindowSize().y;
                currentPlayer->boardPieceShapePtr->setPosition(newPositionInsideTile.first);

                if(updatedPosition.second) /// went through start
                    currentPlayer->money += MONEY_FROM_START;
            }
        }
        while(dices.first == dices.second && timesRolledDouble < 3);
        cout << "Total tiles moved: " << totalMoved << '\n';
        cout << "Position after: " << currentPlayer->getBoardPosition() << '\n';
        ++currentPlayerIterator;

    }*/
}

void Game::eventTextEntered(char chr) {
    for(auto& uiObj : uiManager.elements)
        uiObj.second->onTextEntered(chr);
}

void Game::eventKeyReleased(sf::Keyboard::Key keycode) {

}

void Game::eventWindowResized() {
    std::cout << "New width: " << window.getSize().x << '\n'
              << "New height: " << window.getSize().y << '\n';
}

void Game::eventMousePressed(sf::Mouse::Button click, sf::Vector2i position) {
    if(click == sf::Mouse::Button::Left)
        for(auto &uiElem : uiManager.elements) {
            if (uiElem.second->contains(this->coordinatesToPercentage(Vector2f(position)))) {
                uiElem.second->onClick(click);
            } else {
                uiElem.second->onClickOutside(click);
            }
        }
}

Game::Game() {
    Game::instance = nullptr;
    this->details = "MonOOPoly game by georgiansof";
}

const sf::Font& Game::getDefaultFont() const {
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
    window.create(sf::VideoMode({800, 700}), "MonOOPoly", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    ///window.setFramerateLimit(60);
}
void Game::loop() {
    while(window.isOpen()) {
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    this->eventWindowResized();
                    break;
                case sf::Event::KeyPressed:
                    this->eventKeyPressed(e.key.code);
                    break;
                case sf::Event::KeyReleased:
                    this->eventKeyReleased(e.key.code);
                    break;
                case sf::Event::MouseButtonPressed:
                    this->eventMousePressed(e.mouseButton.button, sf::Mouse::getPosition(window));
                    break;
                case sf::Event::TextEntered:
                    if(e.text.unicode < 128) {
                        this->eventTextEntered(static_cast<char>(e.text.unicode));
                    }
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

SceneManager* Game::getSceneManagerPtr() noexcept {
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
    std::cout<<"Dices: " << int(dice1) << ' ' << int(dice2) << '\n';
    return {dice1,dice2};
}

void Game::nextPlayer() {
    ++this->currentPlayerIterator;
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

float Game::percentageToCoordinate(float perc, Game::axis which) const {
    if(which == Game::axis::X)
        return perc * (float)this->getWindowSize().x;
    else
        return perc * (float)this->getWindowSize().y;
}