#include "../includes/Hard.h"

Hard::Hard() : Difficulty() {}

Hard* Hard::clone() const
{
    return new Hard(*this);
}

int Hard::get_move(const Board& a_board, char a_symbol) const
{
    int size{ a_board.get_size() };
    for (int i = 1; i <= size * size; ++i)
    {
        std::pair<int, int> index{};
        index.first = (i - 1) / size;
        index.second = (i - 1) % size;
        int col{ index.first }, row{ index.second };
        if (a_board.valid_move(col, row) && a_board.win(a_symbol, col, row))
        {
            return i;
        }
        if (a_symbol == 'X')
        {
            a_symbol = 'O';
        }
        else
        {
            a_symbol = 'X';
        }
        if (a_board.valid_move(col, row) && a_board.win(a_symbol, col, row))
        {
            return i;
        }
    }
    int number{ -1 };
    while (number == -1)
    {
        number = 1 + rand() % (size * size);
        std::pair<int, int> index{};
        index.first = (number - 1) / size;
        index.second = (number - 1) % size;
        if (!a_board.valid_move(index.first, index.second))
        {
            number = -1;
        }
    }
    return number;
}
