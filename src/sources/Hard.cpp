#include "../includes/Hard.hpp"

Hard::Hard() : Difficulty() {}

Hard* Hard::clone() const
{
    return new Hard(*this);
}

int Hard::winning_move(const Board& a_board, char a_symbol) const
{
    int size{ a_board.get_size() };
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a_board.valid_move(i, j) && a_board.win(a_symbol, i, j))
            {
                return i * size + j + 1;
            }
        }
    }
    return -1;
}

int Hard::blocking_move(const Board& a_board, char a_symbol) const
{
    char opponent_symbol{ a_symbol == 'X' ? 'O' : 'X' };
    return winning_move(a_board, opponent_symbol);
}

int Hard::get_move(Board& a_board, char a_symbol)
{
    int winning{ winning_move(a_board, a_symbol) };
    if (winning != -1)
    {
        return winning;
    }
    int blocking{ blocking_move(a_board, a_symbol) };
    if (blocking != -1)
    {
        return blocking;
    }
    return Minimax::get_random_move(a_board, a_symbol, "hard");
}
