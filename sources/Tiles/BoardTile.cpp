#include "../../headers/Tiles/BoardTile.hpp"
#include <iostream>

using namespace std;
using namespace sf;

float bigTilePlayerPositionOffsets[3] = {0.03, 0.06, 0.09};

float normalTilePlayerPositionOffsetsX[2] = {0.02, 0.06};
float normalTilePlayerPositionOffsetsY[4] = {0.02, 0.4, 0.06, 0.08};


Vector2f jailOutsidePlayerPositions[8] = {
        {0.12,0.02},
        {0.09, 0.02},
        {0.06, 0.02},
        {0.03, 0.02},
        {0.01, 0.02},
        {0.01, 0.05},
        {0.01,0.08},
        {0.01,0.11}
};

unsigned short BoardTile::getBoardPosition() const noexcept {
    return this->boardPosition;
}

BoardTile::BoardTile(uint16_t boardPosition, BoardTile::Type type)
        : boardPosition(boardPosition), type(type) {
    for(auto &pos : occupiedPosition)
        pos = false;

    float normalTileSize = 0.08;
    float bigTileSize = 0.13;
    float borderSize = 0.01;

    switch(type) {
        case PROPERTY:
        case TAX:
        case CHANCE:
        {
            if(boardPosition >= 1 && boardPosition <= 9)
                for(int x_ind = 0; x_ind < 2; ++x_ind)
                    for(int y_ind = 0; y_ind < 4; ++y_ind)
                        playerPositions[x_ind * 4 + y_ind] = Vector2f(
                                1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 1) - normalTilePlayerPositionOffsetsX[x_ind],
                                1.0f - borderSize - normalTilePlayerPositionOffsetsY[y_ind]
                                );

            if(boardPosition >= 11 && boardPosition<=19)
                for(int y_ind = 0; y_ind < 2; ++y_ind)
                    for(int x_ind = 0; x_ind < 4; ++x_ind)
                        playerPositions[y_ind * 4 + x_ind] = Vector2f(
                                borderSize + normalTilePlayerPositionOffsetsY[x_ind],
                                1.0f - borderSize - bigTileSize - normalTileSize * ((float)boardPosition - 11) - normalTilePlayerPositionOffsetsX[y_ind]
                                );

            if(boardPosition >= 21 && boardPosition <= 29)
                for(int x_ind = 0; x_ind < 2; ++x_ind)
                    for(int y_ind = 0; y_ind < 4; ++y_ind)
                        playerPositions[x_ind * 4 + y_ind] = Vector2f(
                                borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 21) + normalTilePlayerPositionOffsetsX[x_ind],
                                borderSize + normalTilePlayerPositionOffsetsY[y_ind]
                                );

            if(boardPosition >= 31 && boardPosition <= 39)
                for(int y_ind = 0; y_ind < 2; ++y_ind)
                    for(int x_ind = 0; x_ind < 4; ++x_ind)
                        playerPositions[y_ind * 4 + x_ind] = Vector2f(
                                1.0f - borderSize - normalTilePlayerPositionOffsetsY[x_ind],
                                borderSize + bigTileSize + normalTileSize * ((float)boardPosition - 31) + normalTilePlayerPositionOffsetsX[y_ind]
                                );

            break;
        }
        case PARK:
        {
                for(int x_ind = 0; x_ind < 3; ++x_ind)
                    for(int y_ind = 0; y_ind < 3; ++y_ind) {
                        float xOffset = bigTilePlayerPositionOffsets[x_ind] + borderSize;
                        float yOffset = bigTilePlayerPositionOffsets[y_ind] + borderSize;
                        playerPositions[x_ind * 3 + y_ind] = Vector2f(
                                boardPosition == 20 ? xOffset        : 1.0f - xOffset,
                                boardPosition == 0  ? 1.0f - yOffset : yOffset
                                );
                    }

                break;
        }
        case JAIL:
        {
            for(int i = 0; i < 8; ++i)
                playerPositions[i] = jailOutsidePlayerPositions[i];

            break;
        }
    }
}

std::pair<sf::Vector2f, uint8_t> BoardTile::addPlayer() {
    for(int i = 0 ; i < 9; ++i)
        if(!occupiedPosition[i]) {
            occupiedPosition[i] = true;
            return {playerPositions[i], i};
        }
    throw std::runtime_error("Under BoardTile::addPlayer, player position inside tile overflow!");
}