#include "../includes/Board.h"
#include <tabulate/table.hpp>

using namespace tabulate;

Board::Board(int a_size) : m_size(a_size), m_cells(m_size, std::vector<Square>(m_size)), m_winner('-') {}

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

std::ostream& operator<<(std::ostream& a_out, const Board& a_board)
{
    Table full_table, table_left, table_right;
    full_table.format().font_style({FontStyle::bold}).font_align(FontAlign::center);
    for (int i = 0; i < a_board.m_size; ++i)
    {
        str row_left{}, row_right{};
        for (int j = 0; j < a_board.m_size - 1; ++j)
        {
            str Square{ a_board.m_cells[i][j].get_value() };
            if (Square != "X" && Square != "O")
            {
                row_left += ". | ";
                row_right += std::to_string(i * a_board.m_size + j + 1);
                if (a_board.m_size > 3 && i * a_board.m_size + j + 1 < 10)
                {
                    row_right += " ";
                }
                row_right += " | ";
            }
            else
            {
                row_left += Square + " | ";
                row_right += "-";
                if (a_board.m_size > 3)
                {
                    row_right += " ";
                }
                row_right += " | ";
            }
        }
        str Square{ a_board.m_cells[i][a_board.m_size - 1].get_value() };
        if (Square != "X" && Square != "O")
        {
            row_left += ".";
            row_right += std::to_string(i * a_board.m_size + a_board.m_size);
        }
        else
        {
            row_left += Square;
            row_right += "-";
        }
        table_left.add_row({ row_left });
        table_right.add_row({ row_right });

    }
    if (a_board.m_winner == '-')
    {
        full_table.add_row({ table_left, table_right });
    }
    else
    {
        full_table.add_row({ table_left });
    }
    full_table.format().hide_border();
    Scoreboard& scoreboard{ Scoreboard::get_instance() };
    a_out << scoreboard;
    a_out << "\n\n";
    a_out << full_table;
    return a_out;
}

int Board::get_size() const
{
    return m_size;
}

char Board::get_value(int a_row, int a_col) const
{
    return m_cells[a_row][a_col].get_value();
}

char Board::get_winner() const
{
    return m_winner;
}

void Board::set_size(int a_size)
{
    m_size = a_size;
    m_cells.resize(m_size);
    for (int i = 0; i < m_size; ++i)
    {
        m_cells[i].resize(m_size);
    }
}

void Board::set_cell(int a_row, int a_col, char a_value)
{
    m_cells[a_row][a_col].set_value(a_value);
    m_cells[a_row][a_col].set_occupied(true);
}

void Board::clear_cell(int a_row, int a_col)
{
    m_cells[a_row][a_col].set_value(' ');
    m_cells[a_row][a_col].set_occupied(false);
}

void Board::set_winner(char a_winner)
{
    m_winner = a_winner;
}

void Board::set_scoreboard(const std::pair<str, str>& a_names, const std::pair<int, int>& a_wins, int a_draws)
{
    Scoreboard& scoreboard{ Scoreboard::get_instance() };
    scoreboard.initialize(a_names, a_wins, a_draws);
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