#include "../Includes/Square.h"

Square::Square(char a_value, const str& a_free_pos, bool a_occupied)
    : m_value{ a_value }, m_free_pos{ a_free_pos }, m_occupied{ a_occupied }
{
    
}

[[maybe_unused]] std::ostream& operator<<(std::ostream& a_out, const Square& a_square)
{
    if (a_square.m_occupied)
    {
        a_out << a_square.m_value;
    }
    else
    {
        a_out << a_square.m_free_pos;
    }
    return a_out;
}

char Square::get_value() const
{
    return m_value;
}

str Square::get_free_pos() const
{
    return m_free_pos;
}

bool Square::is_occupied() const
{
    return m_occupied;
}

void Square::set_value(char a_value)
{
    m_value = a_value;
}

void Square::set_free_pos(const str& a_free_pos)
{
    m_free_pos = a_free_pos;
}

void Square::set_occupied(bool a_occupied)
{
    m_occupied = a_occupied;
}
