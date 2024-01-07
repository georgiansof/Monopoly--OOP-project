#include "../headers/Player.hpp"
#include "../headers/Game.hpp"
#include "../headers/Tiles/BoardTile.hpp"
#include "../headers/UI/Button.hpp"

using namespace std;
using namespace sf;

volatile bool Player::buyOrPassPressed = false;
volatile bool Player::buying = false;

bool Player::payTo(Player *toWho, uint32_t amount) {
    if(this->money > amount) {
        this->money -= amount;
        toWho += amount;
        Game::getInstancePtr()->updateMoneyLabel();
        std::cout << this->name << " paid " << amount << " to " << toWho->name << '\n';
        return true;
    }

    return false;
}

pair<uint16_t,bool> Player::incrementPosition(int amount) noexcept {
    this->boardPosition += amount;
    bool start = false;
    if(this->boardPosition >= BOARD_TILES_NUMBER) {
        this->boardPosition %= BOARD_TILES_NUMBER;
        start = true;
    }
    return {boardPosition,start};
}

uint16_t Player::getBoardPosition() const noexcept {
    return this->boardPosition;
}

uint8_t Player::getIndexInsideTile() const noexcept {
    return this->indexInsideTile;
}

uint16_t Player::operator++(int) noexcept {return this->incrementPosition().first;}
uint16_t Player::operator++() noexcept {return this->incrementPosition().first;}

PlayerEconomy::PlayerEconomy(uint32_t money) {
    this -> money = money;
}

Color Player::getColor() const noexcept {
    return this->color;
}

[[nodiscard]] const std::string & Player::getName() const noexcept {
    return this->name;
}

void Player::setColorName(sf::Color _color) {
    vector<pair<sf::Color, std::string>> colors {
            {Color::Black, "Black"},
            {Color::Yellow, "Yellow"},
            {Color::Green, "Green"},
            {Color::Red, "Red"},
            {Color::Magenta, "Magenta"},
            {Color::Blue, "Blue"},
            {Color::Cyan, "Cyan"},
            {Color::White, "White"}
    };
    for(auto &colorPair : colors)
        if(colorPair.first == _color) {
            this->colorName = colorPair.second;
            return;
        }
}

Player::Player(const Player& other) : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = new sf::CircleShape(*other.boardPieceShapePtr);
    this->colorName = other.colorName;
}


Player::Player(Player&& other) noexcept : PlayerEconomy(other), PlayerPiece(other) {
    this->boardPosition = other.boardPosition;
    this->name = other.name;
    this->color = other.color;
    this->indexInsideTile = other.indexInsideTile;
    this->boardPieceShapePtr = other.boardPieceShapePtr;
    this->colorName = other.colorName;

    other.boardPosition = -1;
    other.name = "";
    other.color = sf::Color::Transparent;
    other.indexInsideTile = -1;
    other.boardPieceShapePtr = nullptr;
    other.colorName = "";
}

Player& Player::operator=(const Player& other) {
    if(&other != this) {
        this->money = other.money;
        this->boardPosition = other.boardPosition;
        this->name = other.name;
        this->color = other.color;
        this->indexInsideTile = other.indexInsideTile;
        this->boardPieceShapePtr = new sf::CircleShape(*other.boardPieceShapePtr);
    }
    return *this;
}

Player& Player::operator=(Player&& other) noexcept {
    if(&other != this) {
        this->boardPosition = other.boardPosition;
        this->name = other.name;
        this->color = other.color;
        this->indexInsideTile = other.indexInsideTile;
        this->boardPieceShapePtr = other.boardPieceShapePtr;

        other.boardPosition = -1;
        other.name = "";
        other.color = sf::Color::Transparent;
        other.indexInsideTile = -1;
        other.boardPieceShapePtr = nullptr;
    }
    return *this;
}

Player::~Player() {
    delete this->boardPieceShapePtr;
    this->boardPieceShapePtr = nullptr;
}

void Player::moveSpaces(int amount) {
    Game *game = Game::getInstancePtr();
    Board *board = game->getBoardPtr();
    if (!this->inJail)
        board->getTile(this->getBoardPosition()).removePlayer(this->getIndexInsideTile());
    else
        dynamic_cast<Jail &> (board->getTile(this->getBoardPosition())).removePlayerFromJail(this);
    auto updatedPosition = this->incrementPosition(amount);
    auto newPositionInsideTile = board->getTile(updatedPosition.first).addPlayer(this);
    this->indexInsideTile = newPositionInsideTile.second;
    newPositionInsideTile.first.x *= (float) game->getWindowSize().x;
    newPositionInsideTile.first.y *= (float) game->getWindowSize().y;
    this->boardPieceShapePtr->setPosition(newPositionInsideTile.first);
    if (updatedPosition.second) {/// went through start
        this->money += MONEY_FROM_START;
        game->updateMoneyLabel();
    }

}

void Player::sendToJail() {
    Game *game = Game::getInstancePtr();
    Board *board = game->getBoardPtr();
    if(inJail) {
        timesRolledInJail = 0;
        return;
    }
    inJail = true;
    timesRolledInJail = 0;

    board->getTile(this->getBoardPosition()).removePlayer(this);
    auto newPositionInsideTile = dynamic_cast<Jail&> (
            board->getTile(JAIL_TILE_POSITION))
                    .addPlayerToJail(this);
    newPositionInsideTile.first.x *= (float)game->getWindowSize().x;
    newPositionInsideTile.first.y *= (float)game->getWindowSize().y;
    this->boardPieceShapePtr->setPosition(newPositionInsideTile.first);
}

void Player::incrementTimesRolledInJail() {
    ++timesRolledInJail;
}

int Player::getTimesRolledInJail() const noexcept {
    return timesRolledInJail;
}

bool Player::isInJail() const noexcept {
    return this->inJail;
}

const std::string& Player::getColorName() const noexcept {
    return this->colorName;
}

uint32_t PlayerEconomy::getAvailableMoney() const noexcept {
    return this->money;
}

void Player::setBuyOrPassPressed(bool val) {
    buyOrPassPressed = val;
}

void Player::setBuying(bool val) {
    buying = val;
}

void Player::addOwnedProperty(Property *prop) {
    ownedProperties.push_back(prop);
    ///TODO add to UI
}

void Player::waitToPay(Player *toWho, uint32_t amount) {
    std::cout<<"Waiting for " << this->name << " to pay " << amount;
    if(toWho == nullptr)
        cout << " to bank\n";
    else
        cout << " to " << toWho->getName() << '\n';
    while(this->money < amount)
        continue;

    this->money -= amount;
    if(toWho != nullptr)
        toWho->money += amount;

    Game::getInstancePtr()->updateMoneyLabel();
    std::cout<<"Debt paid by "<<this->name<<'\n';
}

void Player::payToBank(uint32_t amount) {
    if(this->money >= amount) {
        this->money -= amount;
        Game::getInstancePtr()->updateMoneyLabel();
        std::cout << this->name << " has paid " << amount << " to bank\n";
    }
    else
        cerr << "PLAYER HAS NOT ENOUGH MONEY TO PAY TO BANK!\n";
}

void Player::buyButtonAction() {
    buyOrPassPressed = true;
    buying = true;
}

void Player::passButtonAction() {
    buyOrPassPressed = true;
    buying = false;
}

bool Player::promptVisitorBuy(Property *prop) {
    Game *game = Game::getInstancePtr();

    if(this->name == game->getHostName()) {

        std::string buyButtonString = "Buy for " + to_string(prop->getPrice()) + "M";

        auto *buyButton = new Button(
                buyButtonString,
                {0.2f, 0.5f},
                {0.1f, 0.05f},
                sf::Color::Yellow,
                sf::Color::Blue,
                OUTLINE_THICKNESS_DEFAULT,
                sf::Color::Green,
                sf::Text::Style::Regular,
                FONTSIZE_DEFAULT,
                &buyButtonAction
        );
        auto *passButton = new Button(
                "Pass",
                {0.35f, 0.5f},
                {0.1f, 0.05f},
                sf::Color::Yellow,
                sf::Color::Blue,
                OUTLINE_THICKNESS_DEFAULT,
                sf::Color::Green,
                sf::Text::Style::Regular,
                FONTSIZE_DEFAULT,
                &passButtonAction
        );

        game->getuiManagerPtr()->addElement("buy_button", buyButton);
        game->getuiManagerPtr()->addElement("pass_button", passButton);

        while (!buyOrPassPressed)
            continue;

        buyOrPassPressed = false;
        game->getuiManagerPtr()->removeElement("buy_button");
        game->getuiManagerPtr()->removeElement("pass_button");
        if(buying) {
            buying = false;
            game->broadcast("buy yes");
            return true;
        }
        game->broadcast("buy no");
        return false;
    }
    else { /// waiting for decision
        cout << "Waiting for " << (*game->getCurrentPlayerIterator())->getName()
             << " to decide \n";
        while(!buyOrPassPressed)
            continue;
        buyOrPassPressed = false;

        cout << (*game->getCurrentPlayerIterator())->getName() << " decided to "
             << (buying ? "" : "not") << " buy" << '\n';

        if(buying) {
            buying = false;
            return true;
        }
        return false;
    }
}