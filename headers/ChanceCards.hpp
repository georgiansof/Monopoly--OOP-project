//
// Created by je_gi on 2023-11-02.
//

#ifndef OOP_CHANCECARD_HPP
#define OOP_CHANCECARD_HPP

#include <string>

class ChanceCard {
    std::string title;
    std::string description;
public:
    ChanceCard(std::string & title, std::string & description)
        : title(title), description(description) {}
    ChanceCard() = delete;
    ~ChanceCard() = default;
    [[nodiscard]] const std::string & getTitle() const noexcept;
    [[nodiscard]] const std::string & getDescription() const noexcept;
    virtual void action() = 0; /// pure virtual function
};

class MoneyCard : public ChanceCard {
    uint32_t sum;
public:
    MoneyCard() = delete;
    ~MoneyCard() = default;
    MoneyCard(std::string & title, std::string & description, uint32_t sum)
        : ChanceCard(title, description), sum(sum) {}
    void action() override;
}; /// TODO ADD TO DESCRIPTION PAY / TAKE SUM

class MoveToTileCard : public ChanceCard {

};

class MoveSpacesCard : public ChanceCard {

};

#endif //OOP_CHANCECARD_HPP
