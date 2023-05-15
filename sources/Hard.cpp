#include "../includes/Hard.h"

Hard::Hard() : Difficulty() {}

Hard* Hard::clone() const
{
    return new Hard(*this);
}

std::pair<int, int> Hard::get_move(const Board& a_board, char a_symbol) const
{
    loading(a_board);
    int size{ a_board.get_size() };
    for (int i = 1; i <= size * size; ++i)
    {
        std::pair<int, int> index{ convert(i, size) };
        int col{ index.first }, row{ index.second };
        if (a_board.valid_move(col, row) && a_board.win(a_symbol, col, row))
        {
            return convert(i, size);
        }
        if (a_symbol == 'X')
        {
            a_symbol = 'O';
        }
        else
        {
            a_symbol = 'X';
        }
        std::cout << i;
        if (a_board.valid_move(col, row) && a_board.win(a_symbol, col, row))
        {
            return convert(i, size);
        }
    }
    int number{ -1 };
    while (number == -1)
    {
        number = 1 + rand() % (size * size);
        std::pair<int, int> index{ convert(number, size) };
        if (!a_board.valid_move(index.first, index.second))
        {
            number = -1;
        }
    }
    return convert(number, size);
}
