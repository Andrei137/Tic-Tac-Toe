#include "Easy.hpp"

Easy::Easy() : Difficulty() {}

Easy* Easy::clone() const
{
    return new Easy(*this);
}

int Easy::get_move(Board& a_board, char a_symbol)
{
    return Minimax::get_random_move(a_board, a_symbol, "easy");
}