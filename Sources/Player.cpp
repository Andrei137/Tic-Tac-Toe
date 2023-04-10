#include "../Includes/Player.h"

int Player::m_draws{0};

Player::Player(char a_symbol) : m_symbol(a_symbol), m_name("Unknown"), m_wins(0)
{
}

std::ostream& operator<<(std::ostream& a_out, const Player& a_player)
{
    a_out << "Player: " << a_player.get_name() << ", Symbol: " << a_player.get_symbol() << ", Wins: " << a_player.get_wins() << ", Draws: " << Player::get_draws() << std::endl;
    return a_out;
}

const str& Player::get_name() const
{
    return m_name;
}

char Player::get_symbol() const
{
    return m_symbol;
}

int Player::get_wins() const
{
    return m_wins;
}

int Player::get_draws()
{
    return m_draws;
}

void Player::set_name(const str& a_name)
{
    m_name = a_name;
}

void Player::set_symbol(char a_symbol)
{
    m_symbol = a_symbol;
}

void Player::set_wins(int a_wins)
{
    m_wins = a_wins;
}

void Player::add_win()
{
    ++m_wins;
}

void Player::add_draw()
{
    ++m_draws;
}

void Player::reset_wins()
{
    m_wins = 0;
}

void Player::reset_draws()
{
    m_draws = 0;
}
