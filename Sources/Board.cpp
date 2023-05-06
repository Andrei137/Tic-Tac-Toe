#include "../Includes/Board.h"

void Board::allocate_memory()
{
    m_cells.resize(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        m_cells[i].resize(m_size);
    }
}

void Board::deallocate_memory()
{
    m_cells.clear();
}

Board::Board(int a_size) : m_size(a_size), m_cells(m_size, std::vector<Square>(m_size)), m_winner('-')
{
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

Board::Board(const Board& a_other) : m_size(a_other.m_size), m_cells(m_size, std::vector<Square>(m_size)), m_winner(a_other.m_winner)
{
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
        m_size = a_other.m_size;
        m_winner = a_other.m_winner;
        m_cells = a_other.m_cells;
    }
    return *this;
}

short Board::nr_digits(int a_n)
{
    short nr{0};
    do
    {
        ++nr;
    }
    while (a_n /= 10);
    return nr;
}

template <typename T>
void Board::display_aux(const str& a_prefix, const str& a_separator, const T* a_ch, bool a_empty) const
{
    if (a_empty)
    {
        std::cout << a_prefix;
        for (int i = 0; i < m_size - 1; ++i)
        {
            std::cout << a_separator;
        }
    }
    else
    {
        std::cout << a_prefix;
        for (int i = 0; i < m_size - 1; ++i)
        {
            std::cout << a_ch[i] << a_separator;
        }
        std::cout << a_ch[m_size - 1];
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
    if (m_winner == '-')
    {
        str* ch1 = new str[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            ch1[i] = { m_cells[a_line][i].get_free_pos() };
        }
        display_aux("\n ", " | ", ch1, false);
        delete[] ch1;
    }
    char* ch2 = new char[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        ch2[i] = { m_cells[a_line][i].get_value() };
        if (ch2[i] != 'X' && ch2[i] != 'O')
        {
            ch2[i] = ' ';
        }
    }
    if (m_winner == '-')
    {
        display_aux("        ", "  |  ", ch2, false);
    }
    else
    {
         display_aux("\n  ", "  |  ", ch2, false);
    }
    delete[] ch2;
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

int Board::get_size() const
{
    return m_size;
}

char Board::get_winner() const
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

void Board::set_winner(char a_winner)
{
    m_winner = a_winner;
}

void Board::reset()
{
    m_winner = '-';
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            m_cells[i][j].set_value(' ');
            m_cells[i][j].set_occupied(false);
            int nr{ i * m_size + j + 1 };
            std::string s{};
            if (nr_digits(m_size * m_size) == 1)
            {
                s = " ";
            }
            int digits{ nr_digits(nr) };
            while (digits < nr_digits(m_size * m_size))
            {
                s += " ";
                ++digits;
            }
            m_cells[i][j].set_free_pos(s + std::to_string(nr) + " ");
        }
    }
}

bool Board::valid_move(int a_row, int a_col) const
{
    return m_cells[a_row][a_col].is_occupied() == false;
}

bool Board::win_col(char a_player, int a_row, int a_col) const
{
    int count{ 1 };
    for (int i = a_row - 1; i >= 0; --i)
    {
        if (m_cells[i][a_col].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
    }
    if (m_size == count || (m_size > 3 && count == 4))
    {
        return true;
    }
    for (int i = a_row + 1; i < m_size; ++i)
    {
        if (m_cells[i][a_col].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
    }
    return false;
}

bool Board::win_row(char a_player, int a_row, int a_col) const
{
    int count{ 1 };
    for (int j = a_col - 1; j >= 0; --j)
    {
        if (m_cells[a_row][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
    }
    if (m_size == count || (m_size > 3 && count == 4))
    {
        return true;
    }
    for (int j = a_col + 1; j < m_size; ++j)
    {
        if (m_cells[a_row][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
    }
    return false;
}

bool Board::win_diag1(char a_player, int a_row, int a_col) const
{
    int count{ 1 };
    int i{ a_row - 1 };
    int j{ a_col - 1 };
    while (i >= 0 && j >= 0)
    {
        if (m_cells[i][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
        --i;
        --j;
    }
    if (m_size == count || (m_size > 3 && count == 4))
    {
        return true;
    }
    i = a_row + 1;
    j = a_col + 1;
    while (i < m_size && j < m_size)
    {
        if (m_cells[i][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
        ++i;
        ++j;
    }
    return false;
}

bool Board::win_diag2(char a_player, int a_row, int a_col) const
{
    int count{ 1 };
    int i{ a_row - 1 };
    int j{ a_col + 1 };
    while (i >= 0 && j < m_size)
    {
        if (m_cells[i][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
        --i;
        ++j;
    }
    if (m_size == count || (m_size > 3 && count == 4))
    {
        return true;
    }
    i = a_row + 1;
    j = a_col - 1;
    while (i < m_size && j >= 0)
    {
        if (m_cells[i][j].get_value() == a_player)
        {
            ++count;
            if (m_size == count || (m_size > 3 && count == 4))
            {
                return true;
            }
        }
        else
        {
            break;
        }
        ++i;
        --j;
    }
    return false;
}

bool Board::win(char a_player, int a_row, int a_col) const
{
    return win_row(a_player, a_row, a_col) || 
           win_col(a_player, a_row, a_col) || 
           win_diag1(a_player, a_row, a_col) || 
           win_diag2(a_player, a_row, a_col);
}

bool Board::draw() const
{
    int count{0};
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            if (m_cells[i][j].get_value() == 'X' || m_cells[i][j].get_value() == 'O')
            {
                ++count;
            }
        }
    }
    return count == m_size * m_size;
}

bool Board::game_over(char a_player, int a_row, int a_col) const
{
    if (a_row == -1 && a_col == -1)
    {
        return false;
    }
    return win(a_player, a_row, a_col) || draw();
}