#include "../includes/Player.h"

int Player::m_draws{0};

Player::Player(char a_symbol) : m_symbol(a_symbol), m_wins(0) {}

Player::Player(const Player& a_other) : m_name(a_other.m_name), m_wins(a_other.m_wins) {}

Player& Player::operator=(const Player& a_other)
{
    if (this == &a_other) 
    {
        return *this;
    }
    m_symbol = a_other.m_symbol;
    m_name = a_other.m_name;
    m_wins = a_other.m_wins;
    return *this;
}

std::ostream& operator<<(std::ostream& a_out, const Player& a_player)
{
    a_out << "Player: " << a_player.get_name() << ", Symbol: " << a_player.get_symbol() << ", Wins: " << a_player.get_wins() << ", Draws: " << Player::get_draws() << '\n';
    return a_out;
}

std::pair<int, int> Player::convert(int a_index, int a_board_size)
{
    int temp{ a_index - 1 };
    int size{ a_board_size };
    return std::make_pair(temp / size, temp % size);
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

void Player::set_symbol(const char& a_symbol)
{
    m_symbol = a_symbol;
}

void Player::set_name(const str& a_name)
{
    m_name = a_name;
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
