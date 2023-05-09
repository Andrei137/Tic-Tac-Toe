#include "../includes/Player.h"
#include <regex>

int Player::m_draws{0};

Player::Player(char a_symbol) : m_symbol(a_symbol), m_wins(0) {}

Player::Player(const Player& a_other) : m_name(a_other.m_name), m_wins(a_other.m_wins) {}

Player& Player::operator=(const Player& a_other)
{
    if (this != &a_other) 
    {
        m_symbol = a_other.m_symbol;
        m_name = a_other.m_name;
        m_wins = a_other.m_wins;
    }
    return *this;
}

std::istream& operator>>(std::istream& a_in, std::shared_ptr<Player>& a_player)
{
    std::regex name_pattern(R"(^[a-zA-Z0-9_!@#$%^&*()\-+=\[\]{};:'\",.<>/?\|`~ ]{1,20}$)");
    bool valid{ false };
    while (!valid)
    {
        try
        {
            std::cout << "(" << a_player->m_symbol << ") Insert name\n-> ";
            std::string temp{};
            a_in >> temp;
            if (!std::regex_match(temp, name_pattern) || a_in.fail() || temp.size() > 20)
            {
                throw NameInputException();
            }
            a_player->m_name = temp;
            valid = true;
        }
        catch (const NameInputException& err)
        {
            rlutil::cls();
            std::cerr << err.what() << '\n';
            rlutil::msleep(2500);
            rlutil::cls();
        }
    }
    return a_in;
}

std::ostream& operator<<(std::ostream& a_out, const Player& a_player)
{
    rlutil::showcursor();
    a_out << "\n\n(" << a_player.m_symbol << ") " << a_player.m_name << "\'";
    if (a_player.m_name[a_player.m_name.size() - 1] != 's')
    {
        a_out << 's';
    }
    a_out << " Turn\n-> ";
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
