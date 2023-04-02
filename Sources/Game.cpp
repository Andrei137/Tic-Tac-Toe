#include "../Includes/Game.h"
#include "../Ext/Rlutil.h"

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

str get_input()
{
    str  input_string{};
    auto last_input_time = std::chrono::steady_clock::now();
#ifndef _WIN32
    struct termios termios_settings;
    tcgetattr(STDIN_FILENO, &termios_settings);
    termios_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_settings);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
#endif
    while (true)
    {
        auto current_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(current_time - last_input_time).count() >= 1)
        {
            if (!input_string.empty())
            {
                break;
            }
            last_input_time = current_time;
        }
#ifdef _WIN32
        if (_kbhit())
        {
            char c = _getch();
            if (c < '0' || c > '9')
            {   
                return "0";
            }
            else
            {
                input_string += c;
            }
            last_input_time = current_time;
        }
#else
        char c;
        int num_read = read(STDIN_FILENO, &c, sizeof(c));
        if (num_read == -1)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                perror("read");
                exit(1);
            }
        }
        else if (num_read == 1)
        {
            if (c < '0' || c > '9')
            {
                return "0";
            }
            else
            {
                input_string += c;
            }
            last_input_time = current_time;
        }
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#ifndef _WIN32
    termios_settings.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_settings);
    fcntl(STDIN_FILENO, F_SETFL, flags);
#endif
    std::cout << std::endl;
    return input_string;
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
        if (a_turn % 2 == 1)
        {
            std::cout << "\n-> (" << m_player1.get_symbol() << ") " << m_player1.get_name() << "\'s Turn";
        }
        else
        {
            std::cout << "\n-> (" << m_player2.get_symbol() << ") " << m_player2.get_name() << "\'s Turn";
        }
        str s{};
        s = get_input();
        int index{ std::stoi(s) };
        if (index > m_board.get_size() * m_board.get_size() || index < 1)
        {
            row = col = -1;
            continue;
        }
        std::pair<int, int> temp{ convert(index) };
        row = temp.first;
        col = temp.second;
        Square sq{ m_board.get_cell(row, col) };
        if (sq.is_occupied())
        {
            row = col = -1;
        }
    }
    if (a_turn % 2 == 1)
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
    }
    if (m_board.draw())
    {
        Player::add_draw();
    }
    else
    {
        if (turn % 2 == 1)
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
}
