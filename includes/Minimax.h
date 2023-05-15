#pragma once

#include "Board.h"

class Minimax
{
    Minimax() = default;
    static const std::vector<int> m_depths;
    static char opponent_symbol(char);
    static int minimax(Board&, int, int, int, bool, char);
    static std::vector<int> get_possible_moves(const Board&, char);
    static std::vector<int> get_moves(Board&, char, const str&);

public:
    static int get_random_move(Board&, char, const str&);
};