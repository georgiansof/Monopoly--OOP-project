#include "../../headers/Tiles/TaxTile.hpp"

using namespace std;

void TaxTile::onVisit(Player *player) {
    if(player->getAvailableMoney() >= this->amount)
        player->payToBank(this->amount);
    else {
        player->waitToPay(nullptr, this->amount); /// TODO payment
        cout<<"Current player has to sell because of insufficient balance!\n";
    }
}