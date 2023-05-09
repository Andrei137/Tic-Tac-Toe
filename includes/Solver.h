#pragma once

#include "AI.h"
#include <unordered_map>

class Solver : public AI
{
    char opponent_symbol() const;
    int evaluate(Board&) const;
    int minimax(Board&, int, int, int, bool) const;

public:
    explicit Solver(char);
    Solver(const Solver&) = default;
    Solver& operator=(const Solver&);
    ~Solver() override = default;

    int get_best_move(Board&) const;
    std::pair<int, int> get_move(const Board&) const override;
};