//
// Created by je_gi on 2024-01-07.
//

#include "../headers/Game.hpp"

using namespace sf;
using namespace std;


void Game::eventKeyPressed(sf::Keyboard::Key keycode) {
    for(auto& uiObj : uiManager.elements)
        uiObj.second->onKeyPress(keycode);

}

void Game::eventTextEntered(char chr) {
    for(auto& uiObj : uiManager.elements)
        uiObj.second->onTextEntered(chr);
}

void Game::eventKeyReleased(sf::Keyboard::Key keycode) {
}

void Game::eventWindowResized(sf::Vector2u windowSizeOld) {
    std::cout << "New width: " << window.getSize().x << '\n'
              << "New height: " << window.getSize().y << '\n';
    sf::Vector2u windowSizeNew = window.getSize();
    sizeMultiplierSinceStartX *= (windowSizeNew.x / windowSizeOld.x);
    sizeMultiplierSinceStartY *= (windowSizeNew.y / windowSizeOld.y);
}

void Game::eventMousePressed(sf::Mouse::Button click, sf::Vector2i position) {
    bool objectOnTopPressed = false;
    if(click == sf::Mouse::Button::Left) {
        if(uiManager.dice1->contains(this->coordinatesToPercentage(Vector2f(position))))
            (new thread([this, click]() {
                this->uiManager.dice1->onClick(click);
            }))->detach();
        else
            if(uiManager.dice2->contains(this->coordinatesToPercentage(Vector2f(position))))
                (new thread([this, click]() {
                    this->uiManager.dice2->onClick(click);
                }))->detach();

        for (auto &uiElem: uiManager.elements) {
            if(uiElem.second != nullptr) {
                if (!uiElem.second->isInvisible() &&
                    uiElem.second->contains(this->coordinatesToPercentage(Vector2f(position)))) {
                    if (!objectOnTopPressed) {
                        (new thread([uiElem, click]() {
                            uiElem.second->onClick(click);
                        }))->detach();
                        objectOnTopPressed = true;
                    }
                } else {
                    if(dynamic_cast<TextEntry*> (uiElem.second))
                        (new thread([uiElem, click]() {
                            uiElem.second->onClickOutside(click);
                        }))->detach();
                }
            }
        }
    }
}

void Game::eventDiceRolled(int dice1, int dice2) {
    Player *currentPlayer = *currentPlayerIterator;
    if(currentPlayer->isInJail())
        if (dice1 != dice2) {
            currentPlayer->incrementTimesRolledInJail();
            if(currentPlayer->getTimesRolledInJail() != 3)
                return;
            else {
                currentPlayer->money -= JAIL_FEE;
            }
            /// and continue making the move
        }
    this->makeMove(dice1,dice2);
}


void Game::eventServerReceivedInput(const std::string& input, ConnectionToClient *fromWho) {
    if(input.starts_with("rolled ")
       || input.starts_with("buy ")
       || input.starts_with("licitation")
       || input.starts_with("bid")
       || input.starts_with("fact_rolled")
            ) {
        eventClientReceivedInput(input); /// as client
        return;
    }

    if(input.starts_with("broadcast ")) {
        std::string message = input.substr(input.find_first_of(' ') + 1);
        broadcastToClients(
                message,
                vector<string>{fromWho->getPeerName()}
        );
        eventServerReceivedInput(message, fromWho);
        return;
    }


    /// ELSE
    std::cout << "Unhandled input event from " << fromWho->getPeerName() << " with request *" << input << "*\n";
}


void Game::eventClientReceivedInput(const std::string &input) {
    /// if....
    /// do...
    /// return

    if(input.starts_with("fact_rolled")) {
        int dice1pos = (int)input.find(' ') + 1;
        int dice2pos = (int)input.find(' ', dice1pos) + 1;
        int dice1 = stoi(input.substr(dice1pos,1));
        int dice2 = stoi(input.substr(dice2pos,1));
        Factory::setDices(dice1, dice2);
        factoryWaitingDiceRoll = false;
        std::cout<<"rolled " << dice1 << ' ' << dice2 << " on a factory\n";
        return;
    }

    if(input.starts_with("rolled")) {
        int namePos = (int)input.find(' ') + 1;//input.find_first_of(' ') + 1;
        int dice1Pos = (int)input.find(' ', namePos) + 1;//(input.substr(namePos)).find_first_of(' ') + 1;
        int dice2Pos = (int)input.find(' ', dice1Pos) + 1;//(input.substr(dice1Pos)).find_first_of(' ') + 1;

        std::string whoRolled = input.substr(namePos, (dice1Pos - 2) - namePos + 1);
        int dice1 = stoi(input.substr(dice1Pos, 1));
        int dice2 = stoi(input.substr(dice2Pos, 1));

        std::cout << whoRolled << " rolled " << dice1 << ' ' << dice2 << '\n';

        eventDiceRolled(dice1, dice2);
        return;
    }
    if(input.starts_with("buy")) {
        int response = (int)input.find(' ') + 1;
        if(input.substr(response).starts_with("yes"))
            Player::setBuying(true);
        else
            Player::setBuying(false);

        Player::setBuyOrPassPressed(true);
        return;
    }
    if(input.starts_with("licitation")) {
        int nextWordPos = (int)input.find(' ') + 1;
        if(input.substr(nextWordPos).starts_with("start")) {
            auto *bidEntry = new TextEntry(
                    {0.3f,0.3f},
                    0.07f,
                    7,
                    TextEntry::NUMBERS
            );
            auto *bidLbl = new Label(
                    "Bid value",
                    *bidEntry
            );
            auto *bidSubmit = new Button(
                    "Submit bid",
                    {0.3f, 0.4f},
                    {0.05f, 0.05f},
                    sf::Color::Blue,
                    sf::Color::Black,
                    OUTLINE_THICKNESS_DEFAULT,
                    sf::Color::Red,
                    sf::Text::Style::Regular,
                    FONTSIZE_DEFAULT,
                    &Game::submitLicitation
            );
            uiManager.addElement("bid_entry", bidEntry);
            uiManager.addElement("bid_label", bidLbl);
            uiManager.addElement("bid_submit", bidSubmit);
            licitationInCourse = true;
        }
        else
            if(input.substr(nextWordPos).starts_with("end")) {
                uiManager.removeElement("bid_entry");
                uiManager.removeElement("bid_label");
                uiManager.removeElement("bid_submit");
                licitationInCourse = false;
                if(this->hostType == Game::SERVER)
                    return;

                /// sync the winner
                int winnerNamePos = (int)input.find(' ', nextWordPos) + 1;
                int winnerPricePos = (int)input.find(' ', winnerNamePos) + 1;

                std::string winnerName = input.substr(winnerNamePos, winnerPricePos - 2 - winnerNamePos + 1);
                uint32_t winnerPrice = stoul(input.substr(winnerPricePos));

                Player *winningPlayer = getPlayerByName(winnerName);

                playerBid winningBid {&winningPlayer->getName(),
                                      winnerPrice};

                this->highestBid = winningBid;
            }

        return;
    }

    if(input.starts_with("bid")) {
        int playerNamePos = (int)input.find(' ') + 1;
        int pricePos = (int)input.find(' ', playerNamePos) + 1;
        string playerName = input.substr(playerNamePos, pricePos - 2 - pricePos + 1);
        uint32_t price = stoul(input.substr(pricePos));
        restartTimer = true;
        if(price > highestBid.load().price) {
            playerBid newHighBid {&getPlayerByName(playerName)->getName(), price};
            highestBid = newHighBid;
        }
        return;
    }

    std::cout << "Unhandled input event from server or self with request *" << input << "*\n";
}


[[maybe_unused]] void Game::clientEventAllConnected(const std::string& playerDetails) {
    this->destroyMainMenuUI();
    this->showBoard(playerDetails);
    this->window.setTitle(std::string("MonOOPoly (role CLIENT) playing as ") + this->hostname + " colored " + this->hostColorName);
    (new thread([this]() {
        this->clientListenToServer();
    }))->detach();
}

