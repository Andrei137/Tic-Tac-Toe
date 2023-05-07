#include "../Includes/Randomizer.h"

Randomizer::Randomizer(char a_symbol) : AI(a_symbol) {}

Randomizer& Randomizer::operator=(const Randomizer& a_other)
{
    if (this == &a_other)
    {
        return *this;
    }
    AI::operator=(a_other);
    return *this;
}

std::pair<int, int> Randomizer::get_move(Board& a_board) const
{
    srand(time(0));
    std::cout << "\nComputer is thinking";
    for (int i = 0; i < 3; ++i)
    {
        rlutil::msleep(100);
        std::cout << '.';
        rlutil::msleep(400);
    }
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