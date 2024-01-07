//
// Created by je_gi on 2023-12-28.
//
#include "../../headers/Tiles/ParkTile.hpp"

using namespace std;

void ParkTile::onVisit(Player *player) {
    if(this->type != ParkTile::GO_TO_JAIL)
        std::cout << "Free parking\n";
    else
        player->sendToJail();
}