#include "../../headers/Tiles/Factory.hpp"
#include "../../headers/Game.hpp"

using namespace std;
using namespace sf;

volatile uint8_t Factory::dice1 = 0;
volatile uint8_t Factory::dice2 = 0;

void Factory::onVisit(Player *plyr) {
    Game *game = Game::getInstancePtr();
    if(this->owner != nullptr) {
        int factoryCount = (int) plyr->getTilesOwnedOfType<Factory>().size();
        game->setFactoryWaitingDiceRoll(true);
        while(game->isFactoryWaitingDiceRoll())
            continue;
        uint32_t feeMult = factoryCount == 1 ? feeMultiplierWithOne : feeMultiplierWithTwo;

        bool successfulPayment = plyr->payTo(owner, (dice1 + dice2) * feeMult);
        if(!successfulPayment) {
            plyr->waitToPay(owner, (dice1 + dice2) * feeMult); /// TODO payment
            cout<<"Current player has to sell because of insufficient balance!\n";
        }
        return;
    }
    /// else if not owned
    Property::offerFromBank(plyr);
}

void Factory::setDices(uint8_t _dice1, uint8_t _dice2) {
    dice1 = _dice1;
    dice2 = _dice2;
}