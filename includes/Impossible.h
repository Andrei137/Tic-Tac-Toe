#pragma once

#include "Difficulty.h"

class Impossible : public Difficulty
{

public:
    Impossible();
    Impossible* clone() const override;

    int get_move(Board&, char) override;
};
