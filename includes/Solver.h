#pragma once

#include "AI.h"

class Solver : public AI
{
    static const std::vector<int> m_depths;

    char opponent_symbol() const;
    int evaluate(Board&) const;
    int minimax(Board&, int, int, int, bool) const;
    int get_best_move(Board&) const;

public:
    explicit Solver(char);
    Solver(const Solver&) = default;
    Solver& operator=(const Solver&);
    ~Solver() override = default;

    std::pair<int, int> get_move(const Board&) const override;
};