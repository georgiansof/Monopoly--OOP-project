//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_CHANCETILE_HPP
#define OOP_CHANCETILE_HPP

#include <vector>
#include <string>

#include "BoardTile.hpp"
#include "ChanceCards.hpp"

class ChanceTile : public BoardTile {
public:
    enum Type {SURPRISE, COMMUNITY};
private:
    static std::vector<ChanceCard*> communityCards;
    static std::vector<ChanceCard*> supriseCards;
    const ChanceTile::Type type;
public:
    ChanceTile(Type type, unsigned short boardPosition);
    ChanceTile() = delete;
    ~ChanceTile() = default;
    void drawCard(Type type);
};

#endif //OOP_CHANCETILE_HPP
