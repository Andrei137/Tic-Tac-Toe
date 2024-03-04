#pragma once

#include "Difficulty.hpp"

class Hard : public Difficulty
{
    int winning_move(const Board&, char) const;
    int blocking_move(const Board&, char) const;

public:
    Hard();
    Hard* clone() const override;

    int get_move(Board&, char) override;
};