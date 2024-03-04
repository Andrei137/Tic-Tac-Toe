#include "Square.hpp"

Square::Square(char a_value, bool a_occupied) : m_value(a_value), m_occupied(a_occupied) {}

Square::Square(const Square& a_other) : m_value(a_other.m_value), m_occupied(a_other.m_occupied) {}

Square& Square::operator=(const Square& a_other)
{
    if (this != &a_other)
    {
        m_value = a_other.m_value;
        m_occupied = a_other.m_occupied;
    }
    return *this;
}

char Square::get_value() const
{
    return m_value;
}

bool Square::is_occupied() const
{
    return m_occupied;
}

void Square::set_value(char a_value)
{
    m_value = a_value;
}


void Square::set_occupied(bool a_occupied)
{
    m_occupied = a_occupied;
}
