#include "../headers/ChanceTile.hpp"

using namespace std;

ChanceTile::ChanceTile(Type type, unsigned short boardPosition)
    : BoardTile(boardPosition, CHANCE), type(type) {
}