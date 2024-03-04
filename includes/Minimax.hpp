#pragma once

#include "Board.hpp"

class Minimax
{
    static Minimax* m_instance;
    static const std::vector<int> m_depths;

    Minimax() = default;

    static char opponent_symbol(char);
    static int minimax(Board&, int, int, int, bool, char);
    static std::vector<int> get_possible_moves(const Board&, char);
    static std::vector<int> get_moves(Board&, char, const str&);

public:
    Minimax(const Minimax&) = delete;
    Minimax& operator=(const Minimax&) = delete;

    static Minimax& get_instance();

    static int get_random_move(Board&, char, const str&);
};