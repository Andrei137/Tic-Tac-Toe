#include "../includes/Scoreboard.h"

Scoreboard& Scoreboard::get_instance()
{
    static Scoreboard instance;
    return instance;
}

void Scoreboard::initialize(const std::pair<str, str>& a_names, const std::pair<int, int>& a_wins, int a_draws)
{
    if (m_wins.first < 0 || m_wins.second < 0 || m_draws < 0)
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
    a_out << "[Draws : " << a_scoreboard.m_draws << "]\n";
    return a_out;
}