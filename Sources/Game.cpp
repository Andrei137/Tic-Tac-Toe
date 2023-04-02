#include "../Includes/Game.h"


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

str Game::get_input(int a_timeout)
{
    str input;
    bool input_started{false};
    int elapsed_time{0};
#ifdef _WIN32
    while (elapsed_time < a_timeout * 1000)
    {
        if (_kbhit())
        {
            char c = _getch();
            if (c < '0' || c > '9')
            {
                return "0";
            }
            else
            {
                input += c;
                input_started = true;
            }
        }
        if (input_started)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            elapsed_time += 125;
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    memset(&newt, 0, sizeof(newt));
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = a_timeout;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (elapsed_time < a_timeout * 1000)
    {
        char buffer[256];
        int num_chars = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (num_chars > 0)
        {
            if (input.size() + num_chars > 255) 
            {
                return "0";
            }
            input.append(buffer, num_chars);
            if (input.back() < '0' || input.back() > '9')
            {
                return "0";
            }
            else
            {
                input_started = true;
            }
        }
        if (input_started)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            elapsed_time += 125;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    return input;
}

std::pair<int, int> Game::convert(int a_index)
{
    int temp{ a_index - 1 };
    int size{ m_board.get_size() };
    return std::make_pair(temp / size, temp % size);
}

void Game::move(int a_turn)
{
    int row{ -1};
    int col{ -1};
    while (row == -1 || col == -1)
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
        std::cout << " Turn";
        str s{ get_input(1) };
        if (s == "404")
        {
            m_board.set_winner('E');
            return;
        }
        int index{0};
        try
        {
            index = std::stoi(s);
        }
        catch (const std::invalid_argument&)
        {
            row = col = -1;
            continue;
        }
        if (index > m_board.get_size() * m_board.get_size() || index < 1)
        {
            row = col = -1;
            continue;
        }
        std::pair<int, int> temp{ convert(index) };
        row = temp.first;
        col = temp.second;
        if (!m_board.valid_move(row, col))
        {
            row = col = -1;
        }
    }
    if (a_turn % 2)
    {
        m_board.set_cell(row, col, m_player1.get_symbol());
    }
    else
    {
        m_board.set_cell(row, col, m_player2.get_symbol());
    }
}

void Game::play()
{
    std::cin >> *this;
    int turn{1};
    while (!m_board.game_over())
    {
        move(turn++);
        if (m_board.get_winner() == 'E')
        {
            rlutil::showcursor();
            rlutil::cls();
            return;
        }
    }
    if (m_board.draw())
    {
        Player::add_draw();
    }
    else
    {
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
