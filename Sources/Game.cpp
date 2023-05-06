#include "../Includes/Game.h"

Game::Game(int a_size) : m_board(a_size), m_gamemode('2'), m_reseted(true)
{
    m_players[0] = std::make_shared<Human>('X');
    m_players[1] = std::make_shared<Human>('O');
}

Game::~Game() = default;

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

std::pair<int, int> Game::move(int a_turn, Board& board, std::array<std::shared_ptr<Player>, 2>& players)
{
    std::pair<int, int> temp{ players[1 - a_turn % 2]->get_move(board) };
    if (temp.first == -1 && temp.second == -1)
    {
        return temp;
    }
    board.set_cell(temp.first, temp.second, players[1 - a_turn % 2]->get_symbol());
    return temp;
}


void Game::print_logo()
{
    std::cout << "\n _______ _        _______           _______ \n";
    std::cout << "|__   __(_)      |__   __|         |__   __| \n";
    std::cout << "   | |   _  ___     | | __ _  ___     | | ___   ___ \n";
    std::cout << "   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n";
    std::cout << "   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n";
    std::cout << "   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n";
}

void Game::play()
{
    if (m_gamemode == '-')
    {
        rlutil::cls();
        print_logo();
        std::cout << "< Number Of Players >\n";
        std::cout << "[1] Player vs Computer\n";
        std::cout << "[2] Player vs Player\n";
        std::cout << "[0] Exit\n\n";
        std::cout << "Option: ";
        m_gamemode = getch();
    }
    // TODO: Implement AI pt 1 
    if (m_gamemode == '1')
    {
        // m_players[1] = std::male_shared<AI>('O');
        rlutil::cls();
        std::cout << "In development...\n";
        return;
    }
    else if (m_gamemode == '2')
    {
        if (m_reseted)
        {
            std::cin >> *this;
        }
        m_board.reset();
        int turn{ 1 };
        std::pair<int, int> temp{ -1, -1 };
        char player{ 'X' };
        while (true)
        {
            std::cout << *this;
            temp = move(turn++, m_board, m_players);
            if (m_board.game_over(player, temp.first, temp.second))
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
        if (m_board.win(player, temp.first, temp.second))
        {
            --turn;
            m_board.set_winner(m_players[1 - turn % 2]->get_symbol());
            m_players[0]->add_win();
        }
        else
        {
            Player::add_draw();
        }
        std::cout << *this;
        char winner{ m_board.get_winner() };
        if (winner != 'X' && winner != 'O')
        {
            std::cout << "\nIt's a draw!\n";
        }
        else
        {
            std::cout << '\n' << m_players[(winner != 'X')]->get_name() << " wins!\n";
        }
        std::cout << "Game over!\n\n";
        std::cout << "Want to replay? [y]es [n]o";
        char replay_decision{};
        replay_decision = getch();
        rlutil::cls();
        if (replay_decision == 'y')
        {
            m_reseted = false;
            std::cout << "Want to replay? yes\n";
            std::cout << "Want to switch sides? [y]es [n]o";
            char sides_decision{};
            sides_decision = getch();
            rlutil::cls();
            if (sides_decision == 'y')
            {
                // swap names and wins
                str temp_name{ m_players[0]->get_name() };
                m_players[0]->set_name(m_players[1]->get_name());
                m_players[1]->set_name(temp_name);
                int temp_wins{ m_players[0]->get_wins() };
                m_players[0]->set_wins(m_players[1]->get_wins());
                m_players[1]->set_wins(temp_wins);
                play();
            }
            else if (sides_decision == 'n')
            {
                play();
            }
            else
            {
                return;
            }
        }
        else if (replay_decision == 'n')
        {
            m_reseted = true;
            m_players[0]->reset_wins();
            m_players[1]->reset_wins();
            Player::reset_draws();
            std::cout << "Want to replay? no\n";
            std::cout << "Want to change players? [y]es [n]o\n";
            char change_players_decision{};
            change_players_decision = getch();
            rlutil::cls();
            if (change_players_decision == 'y')
            {
                play();
            }
            else if (change_players_decision == 'n')
            {
                std::cout << "Want to replay? no\n";
                std::cout << "Want to change players? no\n";
                std::cout << "Want to change gamemode? [y]es [n]o\n";
                char change_gamemode_decision{};
                change_gamemode_decision = getch();
                rlutil::cls();
                if (change_gamemode_decision == 'y')
                {
                    m_gamemode = '-';
                    play();
                }
                else
                {
                    return;
                }
            }
            else 
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        rlutil::cls();
        return;
    }
}
