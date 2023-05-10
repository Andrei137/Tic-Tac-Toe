#include "../includes/StickyNoob.h"

StickyNoob::StickyNoob(char a_symbol) : AI(a_symbol) 
{
    this->set_name("Computer (Easy)");
}

StickyNoob& StickyNoob::operator=(const StickyNoob& a_other)
{
    if (this != &a_other)
    {
        AI::operator=(a_other);
    }
    return *this;
}

std::pair<int, int> StickyNoob::get_move(const Board& a_board) const
{
    loading(a_board);
    char opponent_symbol{ this->get_symbol() == 'X' ? 'O' : 'X' };
    int size{ a_board.get_size() };
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a_board.get_value(i, j) == opponent_symbol)
            {
                if (i != 0 && a_board.valid_move(i - 1, j))
                {
                    return std::make_pair(i - 1, j);
                }
                else if (j != 0 && a_board.valid_move(i, j - 1))
                {
                    return std::make_pair(i, j - 1);
                }
                else if (i != size - 1 && a_board.valid_move(i + 1, j))
                {
                    return std::make_pair(i + 1, j);
                }
                else if (j != size - 1 && a_board.valid_move(i, j + 1))
                {
                    return std::make_pair(i, j + 1);
                }
            }
        }
    }
    return {0, 0};
}