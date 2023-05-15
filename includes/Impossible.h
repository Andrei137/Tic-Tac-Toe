#pragma once

#include "Difficulty.h"

class Impossible : public Difficulty
{
    static const std::vector<int> m_depths;

    char opponent_symbol(char) const;
    int evaluate(Board&, char) const;
    int minimax(Board&, int, int, int, bool, char) const;
    int get_best_move(Board&, char) const;

public:
    Impossible();
    Impossible* clone() const override;

    std::pair<int, int> get_move(const Board&, char) const override;
};
