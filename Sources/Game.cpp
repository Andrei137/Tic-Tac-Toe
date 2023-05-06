#include "../Includes/Game.h"

Game::Game(int a_size) : m_board(a_size), m_gamemode('2'), m_reseted(true)
{
    m_players[0] = std::make_shared<Human>('X');
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
    while (true)
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
            // m_gamemode = getch();
            std::cin >> m_gamemode;
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
                m_players[1] = std::make_shared<Human>('O');
                std::cin >> *this;
            }
            m_board.reset();
            int turn{ 0 };
            int row{ -1 }, col{ -1 };
            char symbol{};
            while (true)
            {
                while (row == -1 && col == -1)
                {
                    std::cout << *this;
                    std::pair<int, int> temp{ m_players[turn % 2]->get_move(m_board) };
                    row = temp.first;
                    col = temp.second;
                    std::cout << row << ' ' << col << '\n';
                    if (row == -1 && col == -1)
                    {
                        m_board.set_winner(' ');
                        row = col = 0;
                    }
                    else if (row < 0 || row >= m_board.get_size() || col < 0 || col >= m_board.get_size())
                    {
                        row = col = -1;
                    }
                    else if (!m_board.valid_move(row, col))
                    {
                        row = col = -1;
                    }
                }
                symbol = m_players[turn % 2]->get_symbol();
                if (m_board.get_winner() == ' ')
                {
                    rlutil::showcursor();
                    rlutil::cls();
                    return;
                }
                else 
                {
                    m_board.set_cell(row, col, symbol);
                    if (m_board.game_over(symbol, row, col))
                    {
                        break;
                    }
                    row = col = -1;
                    ++turn;
                }
            }
            if (m_board.win(symbol, row, col))
            {
                --turn;
                m_board.set_winner(symbol);
                m_players[0]->add_win();
            }
            else
            {
                Player::add_draw();
            }
            char replay_decision{ '-' };
            while (replay_decision == '-')
            {
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
                // replay_decision = getch();
                rlutil::setColor(0);
                std::cin >> replay_decision;
                rlutil::setColor(7);
                rlutil::cls();
                if (replay_decision == 'y')
                {
                    m_reseted = false;
                    char sides_decision{ '-' };
                    while (sides_decision == '-')
                    {
                        std::cout << "Want to replay? yes\n";
                        std::cout << "Want to switch sides? [y]es [n]o";
                        // sides_decision = getch();
                        rlutil::setColor(0);
                        std::cin >> sides_decision;
                        rlutil::setColor(7);
                        rlutil::cls();
                        if (sides_decision == 'y')
                        {
                            std::shared_ptr<Player> temp{ m_players[0] };
                            m_players[0] = m_players[1];
                            m_players[1] = temp;
                            m_players[0]->set_symbol('X');
                            m_players[1]->set_symbol('O');
                        }
                        else if (sides_decision != 'n')
                        {
                            rlutil::cls();
                            sides_decision = '-';
                        }
                    }
                }
                else if (replay_decision == 'n')
                {
                    m_reseted = true;
                    m_players[0]->reset_wins();
                    m_players[1]->reset_wins();
                    Player::reset_draws();
                    char change_players_decision{ '-' };
                    while (change_players_decision == '-')
                    {
                        std::cout << "Want to replay? no\n";
                        std::cout << "Want to change players? [y]es [n]o\n";
                        // change_players_decision = getch();
                        rlutil::setColor(0);
                        std::cin >> change_players_decision;
                        rlutil::setColor(7);
                        rlutil::cls();
                        if (change_players_decision == 'n')
                        {
                            char change_gamemode_decision{ '-' };
                            while (change_gamemode_decision == '-')
                            {
                                std::cout << "Want to replay? no\n";
                                std::cout << "Want to change players? no\n";
                                std::cout << "Want to change gamemode? [y]es [n]o\n";
                                // change_gamemode_decision = getch();
                                rlutil::setColor(0);
                                std::cin >> change_gamemode_decision;
                                rlutil::setColor(7);
                                rlutil::cls();
                                if (change_gamemode_decision == 'y')
                                {
                                    m_gamemode = '-';
                                }
                                else
                                {
                                    return;
                                }
                            }
                        }
                        else if (change_players_decision != 'y')
                        {
                            rlutil::cls();
                            m_gamemode = '-';
                        }
                    }
                }
                else
                {
                    rlutil::cls();
                    replay_decision = '-';
                }
            }
        }
        else
        {
            rlutil::cls();
            return;
        }
    }
}
