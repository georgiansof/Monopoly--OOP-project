#include "../../headers/Tiles/TrainStation.hpp"
#include "../../headers/Game.hpp"

using namespace std;

void TrainStation::onVisit(Player *plyr) {
    if(this->owner != nullptr) {
        int trainStOwnedCount = (int) plyr->getTilesOwnedOfType<TrainStation>().size();
        bool successfulPayment = plyr->payTo(owner, fees[trainStOwnedCount]);
        if(!successfulPayment) {
            plyr->waitToPay(owner, fees[trainStOwnedCount]); /// TODO payment
            cout<<"Current player has to sell because of insufficient balance!\n";
        }
        return;
    }
    /// else if not owned
    Property::offerFromBank(plyr);
}


