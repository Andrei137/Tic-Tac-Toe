#include "../includes/AI.h"

AI::AI(char a_symbol) : Player(a_symbol) {}

AI* AI::clone() const
{
    return new AI(*this);
}

void AI::set_difficulty(std::shared_ptr<Difficulty> a_difficulty)
{
    m_difficulty = a_difficulty;
}

std::pair<int, int> AI::get_move(const Board& a_board) const
{
    if (m_difficulty == nullptr)
    {
        throw initialization_error("Error: The game stopped because the players did not load properly!\n"
                                   "Try restarting the program or contacting the developer\n\n");
    }
    return m_difficulty->get_move(a_board, m_symbol);
}

