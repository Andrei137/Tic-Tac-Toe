#include "..\Includes\Player.h"
#include <fstream>

int Player::m_draws = 0;

Player::Player(char a_symbol, const str& a_name)
    : m_symbol(a_symbol), m_name(a_name), m_wins(0)
{
}

Player::Player(const Player& a_other) = default;

Player& Player::operator=(const Player& other)
{
    if (this != &other) 
    {
        m_name = other.m_name;
        m_symbol = other.m_symbol;
        m_wins = other.m_wins;
    }
    return *this;
}

Player::~Player() = default;

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

void Player::add_win()
{
    ++m_wins;
}

void Player::add_draw()
{
    ++m_draws;
}

void Player::reset_draws()
{
    m_draws = 0;
}

std::ostream& operator<<(std::ostream& a_out, const Player& a_player)
{
    a_out << "Player: " << a_player.get_name() << ", Symbol: " << a_player.get_symbol() << ", Wins: " << a_player.get_wins() << ", Draws: " << Player::get_draws() << std::endl;
    return a_out;
}
