#pragma once

#include "Difficulty.hpp"

class Easy : public Difficulty
{
public:
    Easy();
    Easy* clone() const override;

    int get_move(Board&, char) override;
};