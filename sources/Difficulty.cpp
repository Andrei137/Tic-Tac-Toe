#include "../includes/Difficulty.h"

void Difficulty::loading(const Board& a_board) const
{
    rlutil::cls();
    std::cout << a_board;
    std::cout << "\n\nComputer is thinking";
    for (int i = 0; i < 3; ++i)
    {
        rlutil::msleep(100);
        std::cout << '.';
        rlutil::msleep(400);
    }
}

std::pair<int, int> Difficulty::convert(int a_index, int a_board_size)
{
    int temp{ a_index - 1 };
    int size{ a_board_size };
    return std::make_pair(temp / size, temp % size);
}