#include "../includes/Game.h"

Game::Game(int a_size) : m_board(a_size), m_gamemode('-'), m_difficulty('-'), m_reseted(true)
{
    m_players[0] = std::make_shared<Human>('X');
}

Game::~Game()
{
    rlutil::cls();
    rlutil::showcursor();
    Heart::print_full_heart();
}

std::istream& operator>>(std::istream& a_in, Game& a_game)
{
    rlutil::showcursor();
    rlutil::cls();
    a_in >> a_game.m_players[0];
    const Human* human_ptr{ dynamic_cast<Human*>(a_game.m_players[1].get()) };
    if (human_ptr != nullptr)
    {
        rlutil::cls();
        std::cout << "(X) " << a_game.m_players[0]->get_name() << '\n';
        a_in >> a_game.m_players[1];
    }
    rlutil::cls();
    return a_in;
}

std::ostream& operator<<(std::ostream& a_out, const Game& a_game)
{
    rlutil::cls();
    a_out << a_game.m_board;
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

void Game::print_winner()
{
    std::pair<str, str> names{ m_players[0]->get_name(), m_players[1]->get_name() };
    std::pair<int, int> wins{ m_players[0]->get_wins(), m_players[1]->get_wins() };
    int draws{ Player::get_draws() };
    m_board.set_scoreboard(Scoreboard{ names, wins, draws });
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
}

void Game::play()
{
    if (m_reseted)
    {
        if (m_gamemode == '1')
        {
            if (m_difficulty == '1')
            {
                m_players[1] = std::make_shared<Randomizer>('O');
            }
            else
            {
                m_players[1] = std::make_shared<Solver>('O');
            }
        }
        else
        {
            m_players[1] = std::make_shared<Human>('O');
        }
        std::cin >> *this;
    }
    std::pair<str, str> names{ m_players[0]->get_name(), m_players[1]->get_name() };
    std::pair<int, int> wins{ m_players[0]->get_wins(), m_players[1]->get_wins() };
    int draws{ Player::get_draws() };
    m_board.set_scoreboard(Scoreboard{ names, wins, draws });
    m_board.reset();
    int turn{ 0 };
    int row{ -1 }, col{ -1 };
    char symbol{};
    while (true)
    {
        bool valid{ false };
        while (!valid)
        {
            try
            {
                std::pair<int, int> temp{ m_players[turn % 2]->get_move(m_board) };
                row = temp.first;
                col = temp.second;
                if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size() || !m_board.valid_move(row, col))
                {
                    const Human* human_ptr{ dynamic_cast<Human*>(m_players[turn % 2].get()) };
                    if (human_ptr != nullptr)
                    {
                        rlutil::hidecursor();
                        rlutil::cls();
                        if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size())
                        {
                            row = col = -1;
                            throw OutOfBoundsCellException();
                        }
                        else
                        {
                            row = col = -1;
                            throw NonEmptyCellException();
                        }
                    }
                }
                else if (row == -1 && col == -1)
                {
                    m_board.set_winner(' ');
                    row = col = 0;
                }
                valid = true;
            }
            catch (const OutOfBoundsCellException& err)
            {
                rlutil::cls();
                std::cerr << err.what() << '\n';
                rlutil::msleep(2000);
                rlutil::cls();
            }
            catch (const NonEmptyCellException& err)
            {
                std::cerr << err.what() << '\n';
                rlutil::msleep(2000);
                rlutil::cls();
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
        m_board.set_winner(symbol);
        m_players[turn % 2]->add_win();
    }
    else
    {
        Player::add_draw();
    }
    print_winner();
}

void Game::tictactoe()
{
    while (true)
    {
        // TODO: exceptii pentru user input
        if (m_gamemode == '-')
        {
            rlutil::cls();
            rlutil::showcursor();
            print_logo();
            std::cout << "< Number of players >\n";
            std::cout << "[1] Player vs Computer\n";
            std::cout << "[2] Player vs Player\n";
            std::cout << "[0] Exit\n\n";
            std::cout << "-> ";
            std::cin >> m_gamemode;
        }
        if (m_gamemode == '0')
        {
            rlutil::cls();
            return;
        }
        else if (m_gamemode == '1')
        {
            int wrong_input{ 0 };
            while (m_difficulty == '-')
            {
                rlutil::cls();
                std::cout << "< Difficulty >\n";
                std::cout << "[1] Normal\n";
                std::cout << "[2] Impossible\n";
                std::cout << "[0] Go Back\n\n";
                std::cout << "-> ";
                std::cin >> m_difficulty;
                if (wrong_input == 10)
                {
                    m_gamemode = '1';
                }
                if (m_difficulty == '0')
                {
                    m_gamemode = '-';
                }
                else if (m_difficulty != '1' && m_difficulty != '2')
                {
                    m_difficulty = '-';
                    ++wrong_input;
                }
            }
        }
        if (m_gamemode != '-')
        {
            play();
            char replay_decision{ '-' };
            int wrong_input{ 0 };
            while (replay_decision == '-')
            {
                std::cout << "Want to replay? [y]es [n]o\n-> ";
                std::cin >> replay_decision;
                rlutil::cls();
                if (wrong_input == 10)
                {
                    replay_decision = 'n';
                }
                if (replay_decision == 'y')
                {
                    m_reseted = false;
                    char sides_decision{ '-' };
                    wrong_input = 0;
                    while (sides_decision == '-')
                    {
                        std::cout << "Want to replay? yes\n";
                        std::cout << "Want to switch sides? [y]es [n]o\n-> ";
                        std::cin >> sides_decision;
                        rlutil::cls();
                        if (wrong_input == 10)
                        {
                            sides_decision = 'n';
                        }
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
                            ++wrong_input;
                            sides_decision = '-';
                        }
                    }
                }
                else if (replay_decision == 'n')
                {
                    m_reseted = true;
                    m_players[1] = nullptr;
                    m_players[0]->reset_wins();
                    Player::reset_draws();
                    char change_players_decision{ '-' };
                    wrong_input = 0;
                    while (change_players_decision == '-')
                    {
                        std::cout << "Want to replay? no\n";
                        std::cout << "Want to change players? [y]es [n]o\n-> ";
                        std::cin >> change_players_decision;
                        rlutil::cls();
                        if (wrong_input == 10)
                        {
                            change_players_decision = 'n';
                        }
                        if (change_players_decision == 'y')
                        {
                            m_gamemode = '2';
                        }
                        else if (change_players_decision == 'n')
                        {
                            char change_gamemode_decision{ '-' };
                            while (change_gamemode_decision == '-')
                            {
                                std::cout << "Want to replay? no\n";
                                std::cout << "Want to change players? no\n";
                                std::cout << "Want to change gamemode? [y]es [n]o\n-> ";
                                std::cin >> change_gamemode_decision;
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
                        else
                        {
                            rlutil::cls();
                            ++wrong_input;
                            change_players_decision = '-';
                        }
                    }
                }
                else
                {
                    rlutil::cls();
                    ++wrong_input;
                    replay_decision = '-';
                }
            }
        }
    }
}
