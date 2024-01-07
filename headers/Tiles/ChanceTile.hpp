//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_CHANCETILE_HPP
#define OOP_CHANCETILE_HPP

#include <vector>
#include <string>

#include "BoardTile.hpp"
#include "../ChanceCards.hpp"
#include "../DataStructures/CircularList.hpp"

class ChanceTile : public BoardTile {
public:
    enum Type {SURPRISE, COMMUNITY};
private:
    static CircularList<ChanceCard*> communityCards;
    static CircularList<ChanceCard*> supriseCards;
    const ChanceTile::Type type;
public:
    void onVisit(Player *plyr) override {
        std::cout<<"TO BE IMPLEMENTED Player " << plyr->getName() << "visited tile " << this->getBoardPosition() << '\n';
    }
    ChanceTile(Type type, unsigned short boardPosition);
    ChanceTile() = delete;
    ~ChanceTile() override = default;
    //void drawCard(Type type);
};

#endif //OOP_CHANCETILE_HPP
