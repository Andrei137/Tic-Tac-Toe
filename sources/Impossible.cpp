#include "../includes/Impossible.hpp"
#include <vector>

Impossible::Impossible() : Difficulty() {}

Impossible* Impossible::clone() const
{
    return new Impossible(*this);
}

int Impossible::get_move(Board& a_board, char a_symbol)
{
    /*
        Force the first move of impossible bot to be odd
    */
    if (a_board.get_size() == 3 && a_board.is_empty())
    {
        std::vector<int> best_moves{};
        for (int i = 1; i <= a_board.get_size() * a_board.get_size(); i += 2)
        {
            best_moves.push_back(i);
        }
        return best_moves[rand() % best_moves.size()];
    }
    return Minimax::get_random_move(a_board, a_symbol, "impossible");
}
