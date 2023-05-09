#include "../includes/Randomizer.h"

Randomizer::Randomizer(char a_symbol) : AI(a_symbol) {}

Randomizer& Randomizer::operator=(const Randomizer& a_other)
{
    if (this != &a_other)
    {
        AI::operator=(a_other);
    }
    return *this;
}

std::pair<int, int> Randomizer::get_move(const Board& a_board) const
{
    loading(a_board);
    int size{ a_board.get_size() };
    for (int i = 1; i <= size * size; ++i)
    {
        char symbol{ this->get_symbol() };
        std::pair<int, int> index{ convert(i, size) };
        int col{ index.first }, row{ index.second };
        if (a_board.valid_move(col, row) && a_board.win(symbol, col, row))
        {
            return convert(i, size);
        }
        if (symbol == 'X')
        {
            symbol = 'O';
        }
        else
        {
            symbol = 'X';
        }
        std::cout << i;
        if (a_board.valid_move(col, row) && a_board.win(symbol, col, row))
        {
            return convert(i, size);
        }
    }
    srand(time(0));
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