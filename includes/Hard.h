#pragma once

#include "Difficulty.h"

class Hard : public Difficulty
{
public:
    Hard();
    Hard* clone() const override;

    std::pair<int, int> get_move(const Board&, char) const override;
};