#pragma once

#include "Difficulty.h"

class Easy : public Difficulty
{
public:
    Easy();
    Easy* clone() const override;

    int get_move(const Board&, char) const override;
};