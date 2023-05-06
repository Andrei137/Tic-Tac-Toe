#include "../Includes/Game.h"
#include <Rlutil.h>

Game::Game(int a_size) : m_board(a_size) 
{
    m_players[0] = new Player('X');
    m_players[1] = new Player('O');
}

Game::~Game()
{
    delete m_players[0];
    delete m_players[1];
}

std::istream& operator>>(std::istream& a_in, Game& a_game)
{
    rlutil::cls();
    rlutil::showcursor();
    std::cout << "-> (" << a_game.m_players[0]->get_symbol() << ") Insert name : ";
    str temp{};
    a_in >> temp;
    a_game.m_players[0]->set_name(temp);
    std::cout << "-> (" << a_game.m_players[1]->get_symbol() << ") Insert name : ";
    a_in >> temp;
    a_game.m_players[1]->set_name(temp);
    rlutil::cls();
    return a_in;
}

std::ostream& operator<<(std::ostream& a_out, const Game& a_game)
{
    rlutil::cls();
    a_out << "(" << a_game.m_players[0]->get_symbol() << ") " << a_game.m_players[0]->get_name() << " : " << a_game.m_players[0]->get_wins() << " - ";
    a_out << "(" << a_game.m_players[1]->get_symbol() << ") " << a_game.m_players[1]->get_name() << " : " << a_game.m_players[1]->get_wins() << ' ';
    a_out << "[Draws : " << Player::get_draws() << "]\n";
    a_out << a_game.m_board << '\n';
    return a_out;
}

int Game::read_input(int a_s, int a_idle_s) 
{
    str num{};
    time_t start{}, end{}, idle_start{};
    bool started{ false }, idle_started{ false };
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
                if (idle_started) 
                {
                    time(&idle_start);
                    idle_started = false;
                }
                else if (num.size() > 5) 
                {
                    return 404;
                }
            }
        }
        else 
        {
            if (!idle_started) 
            {
                time(&idle_start);
                idle_started = true;
            }
            time(&end);
            double diff = difftime(end, idle_start);
            if (diff >= a_idle_s || num.size() > 5)
            {
                return 404;
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
    int n{ 0 };
    for (const auto& ch : num) 
    {
        n = n * 10 + (ch - '0');
    }
    return n;
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
            temp_player = m_players[0]->get_name();
            std::cout << "\n-> (" << m_players[0]->get_symbol() << ") " << temp_player << "\'";
        }
        else
        {
            temp_player = m_players[1]->get_name();
            std::cout << "\n-> (" << m_players[1]->get_symbol() << ") " << temp_player << "\'";
        }
        if (temp_player[temp_player.size() - 1] != 's')
        {
            std::cout << 's' ;
        }
        std::cout << " Turn";
        int index{ read_input(1, 60) };
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
        m_board.set_cell(a_row, a_col, m_players[0]->get_symbol());
    }
    else
    {
        m_board.set_cell(a_row, a_col, m_players[1]->get_symbol());
    }
}

void Game::print_logo()
{
    std::cout << "\n _______ _        _______           _______ \n"
                 "|__   __(_)      |__   __|         |__   __| \n"
                 "   | |   _  ___     | | __ _  ___     | | ___   ___ \n"
                 "   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n"
                 "   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n"
                 "   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n";
}

void Game::play(bool a_reseted, char a_preselected_choice)
{
    if (a_preselected_choice == '-')
    {
        rlutil::cls();
        print_logo();
        std::cout << "Select Game Mode : \n\n";
        std::cout << "[1] Player vs Computer\n";
        std::cout << "[2] Player vs Player\n";
        // TODO : Implement Leaderboard
        // std::cout << "[3] Leaderboard\n";
        std::cout << "[3] Exit";
        std::cout << "\n\n-> ";
    }
    char gamemode_decision{ '-' };
    int wrong_gamemode_input{ 0 };
    while (gamemode_decision == '-')
    {
        if (wrong_gamemode_input == 10)
        {
            rlutil::cls();
            return;
        }
        if (a_preselected_choice == '-')
        {
            gamemode_decision = getch();
        }
        else
        {
            gamemode_decision = a_preselected_choice;
        }
        if (gamemode_decision == '1')
        {
            // TODO : Implement AI 
            rlutil::cls();
            return;
        }
        else if (gamemode_decision == '2')
        {
            if (a_reseted)
            {
                std::cin >> *this;
            }
            m_board.reset();
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
                    m_board.set_winner(m_players[0]->get_symbol());
                    m_players[0]->add_win();
                }
                else
                {
                    m_board.set_winner(m_players[1]->get_symbol());
                    m_players[1]->add_win();
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
                std::cout << '\n' << m_players[0]->get_name() << " wins!\n";
            }
            else if (winner == 'O')
            {
                std::cout << '\n' << m_players[1]->get_name() << " wins!\n";
            }
            else
            {
                std::cout << "\nIt's a draw!\n";
            }
            std::cout << "Game Over!\n\n";
            std::cout << "Press Any Key To Continue...";
            getch();
            rlutil::cls();
            std::cout << "Want To Replay? [Y]es [N]o";
            char replay_decision{ '-' };
            int wrong_replay_input{ 0 };
            while (replay_decision == '-')
            {
                if (wrong_replay_input == 10)
                {
                    rlutil::cls();
                    return;
                }
                replay_decision = getch();
                if (replay_decision == 'y')
                {
                    rlutil::cls();
                    std::cout << "Want To Replay? Yes\n";
                    std::cout << "Want To Switch Sides? [Y]es [N]o";
                    char sides_decision{ '-' };
                    int wrong_sides_input{ 0 };
                    while (sides_decision == '-')
                    {
                        if (wrong_sides_input == 10)
                        {
                            rlutil::cls();
                            return;
                        }
                        sides_decision = getch();
                        if (sides_decision == 'y')
                        {
                            rlutil::cls();
                            str aux_name{ m_players[0]->get_name() };
                            m_players[0]->set_name(m_players[1]->get_name());
                            m_players[1]->set_name(aux_name);
                            int aux_wins{ m_players[0]->get_wins() };
                            m_players[0]->set_wins(m_players[1]->get_wins());
                            m_players[1]->set_wins(aux_wins);
                            play(0, '2');
                        }
                        else if (sides_decision == 'n')
                        {
                            rlutil::cls();
                            play(0, '2');
                        }
                        else
                        {
                            sides_decision = '-';
                            ++wrong_sides_input;
                        }
                    }
                }
                else if (replay_decision == 'n')
                {
                    rlutil::cls();
                    m_players[0]->reset_wins();
                    m_players[1]->reset_wins();
                    Player::reset_draws();
                    std::cout << "Want To Replay? No\n";
                    std::cout << "Want To Change Players? [Y]es [N]o\n";
                    char change_decision{ '-' };
                    int wrong_change_input{ 0 };
                    while (change_decision == '-')
                    {
                        if (wrong_change_input == 10)
                        {
                            rlutil::cls();
                            return;
                        }
                        change_decision = getch();
                        if (change_decision == 'y')
                        {
                            rlutil::cls();
                            play(1, '2');
                        }
                        else if (change_decision == 'n')
                        {
                            rlutil::cls();
                            return;
                        }
                        else
                        {
                            change_decision = '-';
                            ++wrong_change_input;
                        }
                    }
                }
                else
                {
                    replay_decision = '-';
                    ++wrong_replay_input;
                }
            }
        }
        else if (gamemode_decision == '3')
        {
            rlutil::cls();
            return;
        }
        else
        {
            gamemode_decision = '-';
            ++wrong_gamemode_input;
        }
    }
}
