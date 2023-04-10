#include "../Includes/Game.h"
#include <Rlutil.h>

Game::Game(int a_size) : m_board(a_size)
{
}

std::istream& operator>>(std::istream& a_in, Game& a_game)
{
    rlutil::cls();
    std::cout << "-> (" << a_game.m_player1.get_symbol() << ") Player one : ";
    str temp{};
    a_in >> temp;
    a_game.m_player1.set_name(temp);
    std::cout << "-> (" << a_game.m_player2.get_symbol() << ") Player two : ";
    a_in >> temp;
    a_game.m_player2.set_name(temp);
    rlutil::cls();
    return a_in;
}

std::ostream& operator<<(std::ostream& a_out, const Game& a_game)
{
    rlutil::cls();
    a_out << "(" << a_game.m_player1.get_symbol() << ") " << a_game.m_player1.get_name() << " : " << a_game.m_player1.get_wins() << " - ";
    a_out << "(" << a_game.m_player2.get_symbol() << ") " << a_game.m_player2.get_name() << " : " << a_game.m_player2.get_wins() << ' ';
    a_out << "[Draws : " << Player::get_draws() << "]\n";
    a_out << a_game.m_board << '\n';
    return a_out;
}

int Game::read_input(int a_s) 
{
    str num{};
    time_t start{}, end{};
    bool started{ false };
    while (true) 
    {
        if (kbhit()) 
        {
            char c = getch();
            if (isdigit(c)) 
            {
                if (!started) 
                {
                    time(&start);
                    started = true;
                }
                num += c;
            }
        }
        if (started) 
        {
            time(&end);
            double diff = difftime(end, start);
            if (diff >= a_s) 
            {
                break;
            }
        }
    }
    return std::accumulate(num.begin(), num.end(), 0, [](int acc, char c) { return acc * 10 + (c - '0'); });
}

std::pair<int, int> Game::convert(int a_index)
{
    int temp{ a_index - 1 };
    int size{ m_board.get_size() };
    return std::make_pair(temp / size, temp % size);
}

void Game::move(int a_turn, int& a_row, int& a_col)
{
    while ((a_row == -1 && a_col == -1) || !m_board.valid_move(a_row, a_col))
    {
        std::cout << *this;
        rlutil::hidecursor();
        str temp_player{};
        if (a_turn % 2)
        {
            temp_player = m_player1.get_name();
            std::cout << "\n-> (" << m_player1.get_symbol() << ") " << temp_player << "\'";
        }
        else
        {
            temp_player = m_player2.get_name();
            std::cout << "\n-> (" << m_player2.get_symbol() << ") " << temp_player << "\'";
        }
        if (temp_player[temp_player.size() - 1] != 's')
        {
            std::cout << 's' ;
        }
        int index{ read_input(1) };
        if (index == 404)
        {
            m_board.set_winner('E');
            return;
        }
        else if (index > m_board.get_size() * m_board.get_size() || index < 1)
        {
            a_row = a_col = -1;
            continue;
        }
        std::pair<int, int> temp{ convert(index) };
        a_row = temp.first;
        a_col = temp.second;
        if (!m_board.valid_move(a_row, a_col))
        {
            a_row = a_col = -1;
        }
    }
    if (a_turn % 2)
    {
        m_board.set_cell(a_row, a_col, m_player1.get_symbol());
    }
    else
    {
        m_board.set_cell(a_row, a_col, m_player2.get_symbol());
    }
}

void Game::play()
{
    std::cin >> *this;
    int turn{ 1 };
    int row{ -1 };
    int col{ -1 };
    char player{ 'X' };
    while (true)
    {
        move(turn++, row, col);
        if (m_board.game_over(player, row, col))
        {
            break;
        }
        else if (m_board.get_winner() == 'E')
        {
            rlutil::showcursor();
            rlutil::cls();
            return;
        }
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    }
    if (m_board.win(player, row, col))
    {
        --turn;
        if (turn % 2)
        {
            m_board.set_winner(m_player1.get_symbol());
            m_player1.add_win();
        }
        else
        {
            m_board.set_winner(m_player2.get_symbol());
            m_player2.add_win();
        }
    }
    else
    {
        Player::add_draw();
    }
    std::cout << *this;
    char winner{ m_board.get_winner() };
    if (winner == 'X')
    {
        std::cout << '\n' << m_player1.get_name() << " wins\n";
    }
    else if (winner == 'O')
    {
        std::cout << '\n' << m_player2.get_name() << " wins\n";
    }
    else
    {
        std::cout << "\nIt's a draw\n";
    }
    std::cout << "Game Over\n\n";
    // De implementat reset
    m_player1.set_symbol('O');
    m_player2.set_symbol('X');
    m_player1.reset_wins();
    m_player2.reset_wins();
    Player::reset_draws();
    rlutil::showcursor();
}
