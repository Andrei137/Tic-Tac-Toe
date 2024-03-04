#include "AI.hpp"

AI::AI(char a_symbol) : Player(a_symbol) {}

AI* AI::clone() const
{
    return new AI(*this);
}

void AI::set_difficulty(std::shared_ptr<Difficulty> a_difficulty)
{
    m_difficulty = std::move(a_difficulty);
}

std::pair<int, int> AI::get_move(const Board& a_board) const
{
    if (m_difficulty == nullptr)
    {
        throw initialization_error("Error: The game stopped because the players did not load properly!\n"
                                   "Try restarting the program or contacting the developer\n\n");
    }
    rlutil::cls();
    std::cout << a_board;
    std::cout << "\n\nComputer is thinking" << std::flush;
    for (int i = 0; i < 3; ++i)
    {
        rlutil::msleep(100);
        std::cout << '.';
        rlutil::msleep(400);
    }
    Board copy{ a_board };
    int move{ m_difficulty->get_move(copy, m_symbol) };
    if (move == -1)
    {
        throw initialization_error("Error: The game stopped because the computer did not work properly!\n" 
                                   "Try restarting the program or contacting the developer\n\n");
    }
    return convert(move, a_board.get_size());
}

