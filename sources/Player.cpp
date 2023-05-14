#include "../includes/Player.h"
#include <chrono>
#include <regex>
#include <thread>

int Player::m_draws{0};

Player::Player(char a_symbol) : m_symbol(a_symbol), m_wins(0) {}

Player::Player(const Player& a_other) : m_name(a_other.m_name), m_wins(a_other.m_wins) {}

Player& Player::operator=(const Player& a_other)
{
    if (this != &a_other) 
    {
        m_name = a_other.m_name;
        m_wins = a_other.m_wins;
        m_symbol = a_other.m_symbol;
    }
    return *this;
}

str Player::get_input(std::istream& a_in) const
{
    bool has_input{ false };
    auto start = std::chrono::steady_clock::now();
    while (!has_input && std::chrono::steady_clock::now() - start < std::chrono::seconds(90))
    {
        if (kbhit())
        {
            has_input = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (!has_input)
    {
        throw timeout_error();
    }
    std::string temp{};
    a_in >> temp;
    return temp;
}

void Player::handle_wrong_input(short& a_wrong_inputs, const str& a_message) const
{
    ++a_wrong_inputs;
    rlutil::hidecursor();
    rlutil::cls();
    std::cerr << a_message;
    rlutil::msleep(2000);
    rlutil::cls();
}

std::istream& operator>>(std::istream& a_in, const std::shared_ptr<Player>& a_player)
{
    std::regex name_pattern(R"(^[a-zA-Z0-9_!@#$%^&*()\-+=\[\]{};:'\",.<>/?\|`~ ]{1,20}$)");
    short wrong_inputs{ 0 };
    while (true)
    {
        rlutil::showcursor();
        if (wrong_inputs == 10)
        {
            throw excessive_attempts_error();
        }
        
        std::cout << "(" << a_player->m_symbol << ") Insert name\n-> ";
        std::string temp{ a_player->get_input(a_in) };
        if (!std::regex_match(temp, name_pattern) || a_in.fail() || temp.size() > 20)
        {
            a_player->handle_wrong_input(wrong_inputs, "Invalid input. Name must be between 1 and 20 characters and only contain letters, numbers, and special characters.");
            continue;
        }
        a_player->m_name = temp;
        return a_in;
    }
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

void Player::reset_draws()
{
    m_draws = 0;
}
