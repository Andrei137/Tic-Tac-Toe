#include "../includes/Human.h"

Human::Human(char a_symbol) : Player(a_symbol) 
{
    this->set_name("Unknown");
}

Human& Human::operator=(const Human& a_other)
{
    if (this != &a_other) 
    {
        Player::operator=(a_other);
    }
    return *this;
}

std::pair<int, int> Human::get_move(const Board& a_board) const
{
    rlutil::showcursor();
    str temp_player{};
    std::cout << "\n-> (" << m_symbol << ") " << m_name << "\'";
    if (m_name[m_name.size() - 1] != 's')
    {
        std::cout << 's';
    }
    std::cout << " Turn : ";
    int index{};
    std::cin >> index;
    if (index == 0)
    {
        return { -1, -1 };
    }
    return convert(index, a_board.get_size());
}
