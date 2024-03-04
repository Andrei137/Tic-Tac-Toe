#include "Scoreboard.hpp"

Scoreboard* Scoreboard::m_instance{ nullptr };

Scoreboard& Scoreboard::get_instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Scoreboard();
    }
    return *m_instance;
}

void Scoreboard::initialize(const std::pair<str, str>& a_names, const std::pair<int, int>& a_wins, int a_draws)
{
    if (a_wins.first < 0 || a_wins.second < 0 || a_draws < 0)
    {
        throw initialization_error("scoreboard");
    }
    m_names = a_names;
    m_wins = a_wins;
    m_draws = a_draws;
}

std::ostream& operator<<(std::ostream& a_out, const Scoreboard& a_scoreboard)
{
    a_out << "(X) " << a_scoreboard.m_names.first << " : " << a_scoreboard.m_wins.first << " - ";
    a_out << "(O) " << a_scoreboard.m_names.second << " : " << a_scoreboard.m_wins.second << ' ';
    a_out << "[Draws : " << a_scoreboard.m_draws << "]\n" << std::flush;
    return a_out;
}