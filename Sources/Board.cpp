#include "../Includes/Board.h"

void Board::allocate_memory()
{
    m_cells = new Square*[m_size];
    for (int i = 0; i < m_size; ++i) 
    {
        m_cells[i] = new Square[m_size];
    }
}

void Board::deallocate_memory()
{
    for (int i = 0; i < m_size; ++i) 
    {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}

short Board::nr_digits(int a_n)
{
    short nr{0};
    do
    {
        ++nr;
    } while (a_n /= 10);
    return nr;
}

template <typename T>
void Board::display_aux(const str& a_s1, const str& a_s2, const T* c, bool empty) const
{
    if (empty)
    {
        std::cout << a_s1;
        for (int i = 0; i < m_size - 1; ++i)
        {
            std::cout << a_s2;
        }
    }
    else
    {
        std::cout << a_s1;
        for (int i = 0; i < m_size - 1; ++i)
        {
            std::cout << c[i] << a_s2;
        }
        std::cout << c[m_size - 1];
    }
}

void Board::display_1() const
{
    str spaces{};
    for (int i = 0; i < nr_digits(m_size * m_size) - 2; ++i)
    {
        spaces += " ";
    }
    display_aux<char>("\n     " + spaces, "|     " + spaces, nullptr, true);
    if (m_winner == '-')
    {
        display_aux<char>("          ", "|     ", nullptr, true);
    }
}

void Board::display_2(int a_line) const
{
    str* ch1 = new str[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        ch1[i] = { m_cells[a_line][i].get_free_pos() };
    }
    display_aux("\n ", " | ", ch1, false);
    delete[] ch1;
    if (m_winner == '-')
    {
        char* ch2 = new char[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            ch2[i] = { m_cells[a_line][i].get_value() };
        }
        display_aux("        ", "  |  ", ch2, false);
        delete[] ch2;
    }
}

void Board::display_3() const
{
    str underlines{};
    for (int i = 0; i < nr_digits(m_size * m_size) - 2; ++i)
    {
        underlines += "_";
    }
    display_aux<char>("\n_____" + underlines, "|_____" + underlines, nullptr, true);
    if (m_winner == '-')
    {
        display_aux<char>("     _____", "|_____", nullptr, true);
    }
}

Board::Board(int a_size) : m_size(a_size), m_cells(nullptr), m_winner('-')
{
    allocate_memory();
    int nr{1}, digits_max{ nr_digits(m_size * m_size) };
    for (int i = 0; i < m_size; ++i) 
    {
        for (int j = 0; j < m_size; ++j) 
        {
            std::string s{};
            if (digits_max == 1)
            {
                s = " ";
            }
            int digits{ nr_digits(nr) };
            while (digits < digits_max)
            {
                s += " ";
                ++digits;
            }
            m_cells[i][j].set_free_pos(s + std::to_string(nr++) + " ");
        }
    }
}

Board::Board(const Board& a_other) : m_size(a_other.m_size), m_cells(nullptr), m_winner(a_other.m_winner)
{
    allocate_memory();
    for (int i = 0; i < m_size; ++i) 
    {
        for (int j = 0; j < m_size; ++j) 
        {
            m_cells[i][j] = a_other.m_cells[i][j];
        }
    }
}

Board::~Board()
{
    deallocate_memory();
}

Board& Board::operator=(const Board& a_other)
{
    if (this != &a_other) 
    {
        deallocate_memory();
        m_size = a_other.m_size;
        m_winner = a_other.m_winner;
        allocate_memory();
        for (int i = 0; i < m_size; ++i) 
        {
            for (int j = 0; j < m_size; ++j) 
            {
                m_cells[i][j] = a_other.m_cells[i][j];
            }
        }
    }
    return *this;
}

std::ostream& operator<< (std::ostream& a_out, const Board& a_board)
{
    for (int i = 0; i < a_board.m_size; ++i)
    {
        a_board.display_1();
        a_board.display_2(i);
        if (i != a_board.m_size - 1)
        {
            a_board.display_3();
        }
        else
        {
            a_board.display_1();
        }
    }
    return a_out;
}

Square Board::get_cell(int a_row, int a_col) const
{
    return m_cells[a_row][a_col];
}

[[maybe_unused]] char Board::get_winner() const
{
    return m_winner;
}

void Board::set_cell(int a_row, int a_col, char a_value)
{
    m_cells[a_row][a_col].set_value(a_value);
    str s{ " - "};
    if (nr_digits(m_size * m_size) == 3)
    {
        s += " ";
    }
    m_cells[a_row][a_col].set_free_pos(s);
    m_cells[a_row][a_col].set_occupied(true);
}

[[maybe_unused]] void Board::set_winner(char a_winner)
{
    m_winner = a_winner;
}
