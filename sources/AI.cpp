#include "../includes/AI.h"

AI::AI(char a_symbol) : Player(a_symbol) {}

AI& AI::operator=(const AI& a_other)
{
    if (this != &a_other)
    {
        Player::operator=(a_other);
    }
    return *this;
}

void AI::loading(const Board& a_board) const
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
