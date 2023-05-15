#include "../includes/Easy.h"

Easy::Easy() : Difficulty() {}

Easy* Easy::clone() const
{
    return new Easy(*this);
}

int Easy::get_move(const Board& a_board, char a_symbol) const
{
    char opponent_symbol{ a_symbol == 'X' ? 'O' : 'X' };
    int size{ a_board.get_size() };
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a_board.get_value(i, j) == opponent_symbol)
            {
                if (i != 0 && a_board.valid_move(i - 1, j))
                {
                    return (i - 1) * size + j + 1;
                }
                else if (j != 0 && a_board.valid_move(i, j - 1))
                {
                    return i * size + j;
                }
                else if (i != size - 1 && a_board.valid_move(i + 1, j))
                {
                    return (i + 1) * size + j + 1;
                }
                else if (j != size - 1 && a_board.valid_move(i, j + 1))
                {
                    return i * size + j + 2;
                }
            }
        }
    }
    return 1;
}