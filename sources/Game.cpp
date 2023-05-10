#include "../includes/Game.h"

Game::Game(int a_size) : m_board(a_size), m_gamemode('-'), m_difficulty('?'), m_reseted(true)
{
    m_players[0] = std::make_shared<Human>('X');
}

Game::~Game()
{
    rlutil::cls();
    rlutil::showcursor();
    Heart::print_full_heart();
}

void Game::swap()
{
    std::shared_ptr<Player> temp{ m_players[0] };
    m_players[0] = m_players[1];
    m_players[1] = temp;
    m_players[0]->set_symbol('X');
    m_players[1]->set_symbol('O');
}

std::istream& operator>>(std::istream& a_in, Game& a_game)
{
    rlutil::cls();
    const Human* human_ptr{ dynamic_cast<Human*>(a_game.m_players[1].get()) };
    if (human_ptr != nullptr)
    {
        a_in >> a_game.m_players[0];
        rlutil::cls();
        std::cout << "(X) " << a_game.m_players[0]->get_name() << '\n';
        a_in >> a_game.m_players[1];
    }
    else
    {
        int random{};
        if (a_game.m_difficulty != '?')
        {
            srand(time(0));
            random = rand() % 2;
        }
        std::cout << "Choosing who goes first";
        for (int i = 0; i < 3; ++i)
        {
            rlutil::msleep(100);
            std::cout << '.';
            rlutil::msleep(400);
        }
        rlutil::cls();
        if (random == 1)
        {
            std::cout << "Computer goes first!\n\n";
            a_game.swap();
            a_in >> a_game.m_players[1];
        }
        else
        {
            std::cout << "Player goes first!\n\n";
            a_in >> a_game.m_players[0];
        }
        rlutil::showcursor();
        rlutil::cls();
    }
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
                m_players[1] = std::make_shared<StickyNoob>('O');
            }
            else if (m_difficulty == '2')
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
                rlutil::cls();
                rlutil::showcursor();
                std::pair<int, int> temp{ m_players[turn % 2]->get_move(m_board) };
                row = temp.first;
                col = temp.second;
                if (row == -1 && col == -1)
                {
                    m_board.set_winner(' ');
                    row = col = 0;
                }
                else if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size() || !m_board.valid_move(row, col))
                {
                    const Human* human_ptr{ dynamic_cast<Human*>(m_players[turn % 2].get()) };
                    if (human_ptr != nullptr)
                    {
                        rlutil::hidecursor();
                        rlutil::cls();
                        if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size())
                        {
                            row = col = -1;
                            throw out_of_bound_error();
                        }
                        else
                        {
                            row = col = -1;
                            throw non_empty_cell_error();
                        }
                    }
                }
                valid = true;
            }
            catch (const out_of_bound_error& err)
            {
                rlutil::hidecursor();
                rlutil::cls();
                std::cerr << err.what() << '\n';
                rlutil::msleep(2000);
                rlutil::cls();
            }
            catch (const non_empty_cell_error& err)
            {
                rlutil::hidecursor();
                rlutil::cls();
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
        while (m_gamemode == '-')
        {
            try
            {
                rlutil::cls();
                rlutil::showcursor();
                print_logo();
                std::cout << "< Number of players >\n";
                std::cout << "[1] Player vs Computer\n";
                std::cout << "[2] Player vs Player\n";
                std::cout << "[0] Exit\n\n";
                std::cout << "-> ";
                str temp{};
                std::cin >> temp;
                if (temp != "0" && temp != "1" && temp != "2")
                {
                    throw number_of_players_error();
                }
                m_gamemode = temp[0];
            }
            catch (const number_of_players_error& err)
            {
                rlutil::hidecursor();
                rlutil::cls();
                std::cerr << err.what() << '\n';
                rlutil::msleep(2000);
            }
        }
        if (m_gamemode == '0')
        {
            rlutil::cls();
            return;
        }
        else if (m_gamemode == '1')
        {
            if (m_difficulty == '?')
            {
                m_difficulty = '-';
            }
            while (m_difficulty == '-')
            {
                try
                {
                    rlutil::cls();
                    rlutil::showcursor();
                    std::cout << "< Difficulty >\n";
                    std::cout << "[1] Easy\n";
                    std::cout << "[2] Normal\n";
                    std::cout << "[3] Impossible\n";
                    std::cout << "[0] Go Back\n\n";
                    std::cout << "-> ";
                    str temp{};
                    std::cin >> temp;
                    if (temp != "0" && temp != "1" && temp != "2" && temp != "3")
                    {
                        throw difficulty_error();
                    }
                    m_difficulty = temp[0];
                    if (m_difficulty == '0')
                    {
                        m_gamemode = '-';
                        m_difficulty = '?';
                    }
                }
                catch (const difficulty_error& err)
                {
                    rlutil::hidecursor();
                    rlutil::cls();
                    std::cerr << err.what() << '\n';
                    rlutil::msleep(2000);
                }
            }
        }
        if (m_gamemode != '-')
        {
            play();
            char replay_decision{ '-' };
            while (replay_decision == '-')
            {
                try
                {
                    rlutil::showcursor();
                    std::cout << "Want to replay? [y]es [n]o\n-> ";
                    str temp{};
                    std::cin >> temp;
                    if (temp != "y" && temp != "n")
                    {
                        throw replay_error();
                    }
                    replay_decision = temp[0];
                    rlutil::cls();
                }
                catch (const replay_error& err)
                {
                    rlutil::hidecursor();
                    rlutil::cls();
                    std::cerr << err.what() << '\n';
                    rlutil::msleep(2000);
                    rlutil::cls();
                }
            }
            if (replay_decision == 'y')
            {
                m_reseted = false;
                char sides_decision{ '-' };
                while (sides_decision == '-')
                {
                    try
                    {
                        rlutil::cls();
                        rlutil::showcursor();
                        std::cout << "Want to replay? yes\n";
                        std::cout << "Want to switch sides? [y]es [n]o\n-> ";
                        str temp{};
                        std::cin >> temp;
                        if (temp != "y" && temp != "n")
                        {
                            throw replay_error();
                        }
                        sides_decision = temp[0];
                        rlutil::cls();
                    }
                    catch (const replay_error& err)
                    {
                        rlutil::hidecursor();
                        rlutil::cls();
                        std::cerr << err.what() << '\n';
                        rlutil::msleep(2000);
                    }
                }
                if (sides_decision == 'y')
                {
                    swap();
                }
            }
            else
            {
                m_reseted = true;
                m_players[1] = nullptr;
                m_players[0]->reset_wins();
                Player::reset_draws();
                char change_players_decision{ '-' };
                while (change_players_decision == '-')
                {
                    try
                    {
                        rlutil::cls();
                        rlutil::showcursor();
                        std::cout << "Want to replay? no\n";
                        std::cout << "Want to change players? [y]es [n]o\n-> ";
                        str temp{};
                        std::cin >> temp;
                        if (temp != "y" && temp != "n")
                        {
                            throw replay_error();
                        }
                        change_players_decision = temp[0];
                        rlutil::cls();
                    }
                    catch (const replay_error& err)
                    {
                        rlutil::hidecursor();
                        rlutil::cls();
                        std::cerr << err.what() << '\n';
                        rlutil::msleep(2000);
                    }
                }
                if (change_players_decision == 'n')
                {
                    char change_difficulty_decision{ '-' };
                    if (m_difficulty != '-' && m_difficulty != '?')
                    {
                        while (change_difficulty_decision == '-')
                        {
                            try
                            {
                                rlutil::cls();
                                rlutil::showcursor();
                                std::cout << "Want to replay? no\n";
                                std::cout << "Want to change players? no\n";
                                std::cout << "Want to change difficulty? [y]es [n]o\n-> ";
                                str temp{};
                                std::cin >> temp;
                                if (temp != "y" && temp != "n")
                                {
                                    throw replay_error();
                                }
                                change_difficulty_decision = temp[0];
                                rlutil::cls();
                            }
                            catch (const replay_error& err)
                            {
                                rlutil::hidecursor();
                                rlutil::cls();
                                std::cerr << err.what() << '\n';
                                rlutil::msleep(2000);
                            }
                        }
                        if (change_difficulty_decision == 'y')
                        {
                            m_difficulty = '-';
                        }
                    }
                    if (change_difficulty_decision == '-' || change_difficulty_decision == 'n')
                    {
                        char change_gamemode_decision{ '-' };
                        while (change_gamemode_decision == '-')
                        {
                            try
                            {
                                rlutil::cls();
                                rlutil::showcursor();
                                std::cout << "Want to replay? no\n";
                                std::cout << "Want to change players? no\n";
                                if (change_difficulty_decision == 'n')
                                {
                                    std::cout << "Want to change difficulty? no\n";
                                }
                                std::cout << "Want to change gamemode? [y]es [n]o\n-> ";
                                str temp{};
                                std::cin >> temp;
                                if (temp != "y" && temp != "n")
                                {
                                    throw replay_error();
                                }
                                change_gamemode_decision = temp[0];
                                rlutil::cls();
                            }
                            catch (const replay_error& err)
                            {
                                rlutil::hidecursor();
                                rlutil::cls();
                                std::cerr << err.what() << '\n';
                                rlutil::msleep(2000);
                            }
                        }
                        if (change_gamemode_decision == 'y')
                        {
                            m_gamemode = m_difficulty = '-';
                        }
                        else
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
}
