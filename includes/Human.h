#pragma once

#include "Player.h"

class Human : public Player
{
public:
    explicit Human(char);
    Human(const Human&) = default;
    Human& operator=(const Human&);
    ~Human() override = default;

    std::pair<int, int> get_move(const Board&) const override;
};
