#include "../headers/Game.hpp"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <random>
#include "../headers/external/json.hpp"
#include "../constants.hpp"
#include "../headers/DataStructures/CustomExceptions.hpp"

using json = nlohmann::json;

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
}

sf::Vector2<unsigned int> Game::getScreenSize() const {
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
        throw insufficientTilesException(board.getTileCount());
}

void Game::addPlayer(Player *playerPtr) {
    if(this->players.size() >= 8)
        throw playerCountException(playerPtr->getName());

    this->players.push_back(playerPtr);
    if(this->currentPlayerIterator == players.end()) /// first inserted player
        this->currentPlayerIterator = players.begin();

    auto playerPositionPair = board.getTile(0).addPlayer();

    sf::Vector2<float> playerPiecePosition = playerPositionPair.first;
    playerPtr->setIndexInsideTile(playerPositionPair.second);

    int screenX = (int)this->getScreenSize().x;
    int screenY = (int)this->getScreenSize().y;

    playerPiecePosition.x *= screenX;
    playerPiecePosition.y *= screenY;

    auto playerPieceRadius = (float) std::min(screenX, screenY) / 48 / 2;
    auto playerPieceShapePtr = new sf::CircleShape();
    playerPieceShapePtr->setRadius(playerPieceRadius);
    playerPieceShapePtr->setPosition(playerPiecePosition);
    playerPieceShapePtr->setFillColor(playerPtr->getColor());
    playerPieceShapePtr->setOutlineThickness(1.5);
    playerPieceShapePtr->setOutlineColor(sf::Color::Black);
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

void Game::nextPlayer() {
    ++this->currentPlayerIterator;
}