#pragma once

#include "Difficulty.h"

class Hard : public Difficulty
{
public:
    Hard();
    Hard* clone() const override;

    int get_move(const Board&, char) const override;
};