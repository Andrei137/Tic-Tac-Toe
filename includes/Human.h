#pragma once

#include "Player.h"

class Human : public Player
{
public:
    explicit Human(char);
    Human(const Human&) = default;
    Human* clone() const override;
    Human& operator=(const Human&);
    ~Human() override = default;

    void set_difficulty(std::shared_ptr<Difficulty>) override;

    std::pair<int, int> get_move(const Board&) const override;
};
