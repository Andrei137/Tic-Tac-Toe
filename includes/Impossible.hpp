#pragma once

#include "Difficulty.hpp"

class Impossible : public Difficulty
{

public:
    Impossible();
    Impossible* clone() const override;

    int get_move(Board&, char) override;
};