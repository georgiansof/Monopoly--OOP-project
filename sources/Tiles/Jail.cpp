//
// Created by je_gi on 2023-11-16.
//
#include "../../headers/Tiles/Jail.hpp"

float jailTilePlayerPositionsInsideOffsets[3] = {0.06, 0.09, 0.12};

Jail::Jail() : BoardTile(10, BoardTile::JAIL) {
    float borderSize = 0.01;
    for(int x_ind = 0; x_ind < 3; ++x_ind)
        for(int y_ind = 0; y_ind < 3; ++y_ind)
            playerPositionsImprisoned[x_ind * 3 + y_ind] = sf::Vector2f(
                    borderSize + jailTilePlayerPositionsInsideOffsets[x_ind],
                    1.0f - borderSize - jailTilePlayerPositionsInsideOffsets[y_ind]
                    );
    for(int i = 0; i < 9; ++i)
        occupiedPositionsImprisoned[i] = nullptr;
}
std::pair<sf::Vector2f, uint8_t> Jail::addPlayerToJail(Player *playerPtr) {
    for(int i = 0 ; i < 9; ++i)
        if(!occupiedPositionsImprisoned[i]) {
            occupiedPositionsImprisoned[i] = playerPtr;
            return {playerPositionsImprisoned[i], i};
        }
    throw std::runtime_error("Under Jail::addPlayer, player position inside tile overflow!");
}

[[maybe_unused]] void Jail::removePlayerFromJail(uint8_t positionInsideTileJailed) {
    occupiedPositionsImprisoned[positionInsideTileJailed] = nullptr;
}

void Jail::removePlayerFromJail(Player *playerPtr) {
    for(auto& p : this->occupiedPositions)
        if(p == playerPtr)
            p = nullptr;
}