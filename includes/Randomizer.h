#pragma once

#include "AI.h"

class Randomizer : public AI
{
public:
    explicit Randomizer(char);
    Randomizer(const Randomizer&) = default;
    Randomizer& operator=(const Randomizer&);
    ~Randomizer() override = default;

    std::pair<int, int> get_move(const Board&) const override;
};
