#pragma once

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <rlutil.h>

template <short Size>
Game<Size>::Game(std::array<std::shared_ptr<Player>, 2> a_players, char a_gamemode, char a_difficulty, bool a_reseted) 
    : m_players{a_players[0], a_players[1]}, m_board(Size), m_gamemode(a_gamemode), m_difficulty(a_difficulty), m_reseted(a_reseted), m_changed_size(Size)
{
    if constexpr (Size < 3 || Size > 9)
    {
        throw initialization_error("Error: The game stopped because the board did not load properly!\n"
                                   "Try restarting the program or contacting the developer\n\n");
    }
}

template <short Size>
Game<Size>::Game(const Game<Size>& a_other) : m_players(a_other.m_players), m_board(a_other.m_board), m_gamemode(a_other.m_gamemode), m_difficulty(a_other.m_difficulty), m_reseted(a_other.m_reseted), m_changed_size(a_other.m_changed_size)
{
}

template <short Size>
Game<Size>& Game<Size>::operator=(const Game<Size>& a_other)
{
    if (this != &a_other)
    {
        m_players = a_other.m_players;
        m_board = a_other.m_board;
        m_gamemode = a_other.m_gamemode;
        m_difficulty = a_other.m_difficulty;
        m_reseted = a_other.m_reseted;
        m_changed_size = a_other.m_changed_size;
    }
    return *this;
}

template <short Size>
void Game<Size>::create_AI(int a_difficulty, int a_index, char a_symbol)
{
    if (a_difficulty == 1)
    {
        m_players[a_index] = AIFactory::easy(a_symbol);
        m_players[a_index]->set_name("Computer (Easy)");
    }
    else if (a_difficulty == 2)
    {
        m_players[a_index] = AIFactory::hard(a_symbol);
        m_players[a_index]->set_name("Computer (Hard)");
    }
    else
    {
        m_players[a_index] = AIFactory::impossible(a_symbol);
        m_players[a_index]->set_name("Computer (Impossible)");
    }
}

template <short Size>
std::istream& operator>>(std::istream& a_in, Game<Size>& a_game)
{
    if (a_game.m_players[0]->get_symbol() != 'X')
    {
        throw initialization_error("Error: The game stopped because the player order did not load properly!\n"
                                   "Try restarting the program or contacting the developer\n\n");
    }
    rlutil::cls();
    const Human* human_ptr{ dynamic_cast<Human*>(a_game.m_players[1].get()) };
    if (human_ptr != nullptr)
    {
        a_in >> a_game.m_players[0];
        rlutil::cls();
        std::cout << "(X) " << a_game.m_players[0]->get_name() << '\n' << std::flush;
        a_in >> a_game.m_players[1];
        return a_in;
    }
    human_ptr = dynamic_cast<Human*>(a_game.m_players[0].get());
    if (human_ptr != nullptr)
    {
        if (a_game.m_players[1]->get_name() == "Unknown")
        {
            throw initialization_error("Error: The game stopped because the computer did not load properly!\n" 
                                       "Try restarting the program or contacting the developer\n\n");
        }
        int random{};
        if (a_game.m_difficulty != '?')
        {
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
            a_game.swap_players();
            a_in >> a_game.m_players[1];
        }
        else
        {
            std::cout << "Player goes first!\n\n";
            a_in >> a_game.m_players[0];
            rlutil::showcursor();
            rlutil::cls();
        }
    }
    str name{ a_game.m_players[0]->get_name() };
    if (name == a_game.m_players[1]->get_name())
    {
        /*
            Get difficulty from between () from temp to fix duplicated names
            Compuer (Impossible) -> Impossible
        */
        name = name.substr(name.find('('), name.find(')') - name.find('(') + 1);
        a_game.m_players[0]->set_name("Computer 1 " + name);
        a_game.m_players[1]->set_name("Computer 2 " + name);
    }
    return a_in;
}

template <short Size>
std::ostream& operator<<(std::ostream& a_out, const Game<Size>& a_game)
{
    rlutil::cls();
    a_out << a_game.m_board << std::flush;
    return a_out;
}

template <short Size>
void Game<Size>::print_logo()
{
    std::cout << "\n _______ _        _______           _______ \n";
    std::cout << "|__   __(_)      |__   __|         |__   __| \n";
    std::cout << "   | |   _  ___     | | __ _  ___     | | ___   ___ \n";
    std::cout << "   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n";
    std::cout << "   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n";
    std::cout << "   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n" << std::flush;
}

template <short Size>
void Game<Size>::print_winner()
{
    std::pair<str, str> names{ m_players[0]->get_name(), m_players[1]->get_name() };
    std::pair<int, int> wins{ m_players[0]->get_wins(), m_players[1]->get_wins() };
    m_board.set_scoreboard(names, wins, Player::get_draws());
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
    std::cout << "Game over!\n\n" << std::flush;
}

template <short Size>
std::pair<int, int> Game<Size>::get_move(int a_turn)
{
    short wrong_inputs{ 0 };
    while (true)
    {
        if (wrong_inputs == 10)
        {
            throw excessive_attempts_error();
        }
        rlutil::cls();
        rlutil::showcursor();
        std::pair<int, int> temp{ m_players[a_turn % 2]->get_move(m_board) };
        int row { temp.first };
        int col { temp.second };
        if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size() || !m_board.valid_move(row, col))
        {
            ++wrong_inputs;
            const Human* human_ptr{ dynamic_cast<Human*>(m_players[a_turn % 2].get()) };
            if (human_ptr != nullptr)
            {
                str message{ "Invalid move. Please choose an empty cell!\n" };
                if (row < 0 || col < 0 || row >= m_board.get_size() || col >= m_board.get_size())
                {
                    message = "Invalid input. Please choose a cell within the board!\n";
                }
                m_players[0]->handle_wrong_input(wrong_inputs, message);
            }
            continue;
        }
        return temp;
    }
}

template <short Size>
char Game<Size>::make_decision(const str& a_message, const str& a_options)
{
    short wrong_inputs{ 0 };
    while (true)
    {
        rlutil::cls();
        rlutil::showcursor();
        if (wrong_inputs == 10)
        {
            throw excessive_attempts_error();
        }
        if (m_gamemode == '?')
        {
            print_logo();
        }
        else if (m_board.get_winner() != '-')
        {
            print_winner();
        }
        std::cout << a_message << "\n-> " << std::flush;
        str temp{ Player::get_input(std::cin) };
        if (temp.size() != 1 || a_options.find(temp[0]) == str::npos)
        {
            Player::handle_wrong_input(wrong_inputs, "Invalid input! Please try again!");
            continue;
        }
        return temp[0];
    }
}

template <short Size>
void Game<Size>::set_gamemode(char a_gamemode)
{
    m_gamemode = a_gamemode; 
}

template <short Size>
void Game<Size>::set_difficulty(char a_difficulty)
{
    m_difficulty = a_difficulty;
}

template <short Size>
players Game<Size>::get_players() const
{
    return m_players;
}

template <short Size>
char Game<Size>::get_gamemode() const
{
    return m_gamemode;
}

template <short Size>
char Game<Size>::get_difficulty() const
{
    return m_difficulty;
}

template <short Size>
bool Game<Size>::get_reseted() const
{
    return m_reseted;
}

template <short Size>
short Game<Size>::get_changed_size() const
{
    return m_changed_size;
}

template <short Size>
void Game<Size>::swap_players()
{
    std::shared_ptr<Player> temp_player{ m_players[0]->clone() };
    m_players[0] = std::move(m_players[1]);
    m_players[1] = std::move(temp_player);

    m_players[0]->set_symbol('X');
    m_players[1]->set_symbol('O');
}

template <short Size>
void Game<Size>::initialize()
{
    if (m_gamemode == '?')
    {
        m_gamemode = make_decision
        (
            "< Choose the gamemode >\n"
            "[1] Computer vs Computer\n"
            "[2] Player vs Computer\n"
            "[3] Player vs Player\n"
            "[4] Change the board size\n"
            "[0] Exit\n",
            "01234"
        );
    }
    if (m_gamemode == '0')
    {
        rlutil::cls();
        return;
    }
    else if (m_gamemode == '2')
    {
        if (m_difficulty == '?')
        {
            m_difficulty = make_decision
            (
                "< Difficulty >\n"
                "[1] Easy\n"
                "[2] Hard\n"
                "[3] Impossible\n"
                "[0] Go back\n",
                "0123"
            );
        }
        if (m_difficulty == '0')
        {
            m_gamemode = m_difficulty = '?';
            initialize();
        }
    }
    else if (m_gamemode == '4')
    {
        char size = make_decision
        (
            "< Choose the board size >\n"
            "[?] Select any number from 3 to 9\n"
            "[0] Go back\n",
            "03456789"
        );
        if (size != '0')
        {
            m_changed_size = size - '0';
        }
        m_gamemode = '?';
        initialize();
    }
    return;
}

template <short Size>
void Game<Size>::replay()
{
    std::stringstream ss{};
    ss << "Want to replay? ";
    char replay_decision
    { 
        make_decision
        (
            ss.str() + "[y]es [n]o",
            "yn"
        ) 
    };
    if (replay_decision == 'y')
    {
        ss << "yes\n"
              "Want to switch sides? ";
        m_reseted = false;
        char sides_decision
        {
            make_decision
            (
                ss.str() + "[y]es [n]o",
                "yn"
            )
        };
        if (sides_decision == 'y')
        {
            swap_players();
        }
        return;
    }
    ss << "no\n"
          "Want to change players? ";
    m_reseted = true;
    Player::reset_draws();
    char change_players_decision
    {
        make_decision
        (
            ss.str() + "[y]es [n]o",
            "yn"
        )
    };
    if (change_players_decision == 'y')
    {
        return;
    }
    char change_difficulty_decision{ '-' };
    if (m_difficulty != '?')
    {
        ss << "no\n"
              "Want to change difficulty? ";
        change_difficulty_decision = make_decision
        (
            ss.str() + "[y]es [n]o",
            "yn"
        );
    }
    if (change_difficulty_decision == 'y')
    {
        m_board.set_winner('-');
        m_difficulty = '?';
        return;
    }
    ss << "no\n"
          "Want to change gamemode? ";
    char change_gamemode_decision{};
    if (change_difficulty_decision == '-')
    {
        change_gamemode_decision = make_decision
        (
            ss.str() + "[y]es [n]o",
            "yn"
        );
    }
    else if (change_difficulty_decision == 'n')
    {
        change_gamemode_decision =
        {  
            make_decision
            (
                ss.str() + "[y]es [n]o",
                "yn"
            )
        };
    }
    if (change_gamemode_decision == 'n')
    {
        rlutil::cls();
        m_gamemode = '0';
        return;
    }
    m_board.set_winner('-');
    m_gamemode = m_difficulty = '?';
}

template <short Size>
void Game<Size>::play()
{
    m_board.reset();
    for (int i = 0; i < m_board.get_size(); ++i)
    {
        for (int j = 0; j < m_board.get_size(); ++j)
        {
            if (!m_board.valid_move(i, j))
            {
                throw initialization_error("Error: The game stopped because the board did not load properly!\n"
                                           "Try restarting the program or contacting the developer\n\n");
            }
        }
    }
    if (m_reseted)
    {
        // delete both players
        m_players[0] = nullptr;
        m_players[1] = nullptr;
        if (m_gamemode == '1')
        {
            create_AI(1 + rand() % 3, 0, 'X');
            create_AI(1 + rand() % 3, 1, 'O');
        }
        else if (m_gamemode == '2')
        {
            m_players[0] = std::make_shared<Human>('X');
            create_AI(m_difficulty - '0', 1, 'O');
        }
        else
        {
            m_players[0] = std::make_shared<Human>('X');
            m_players[1] = std::make_shared<Human>('O');
        }
        std::cin >> *this;
    }
    std::pair<str, str> names{ m_players[0]->get_name(), m_players[1]->get_name() };
    std::pair<int, int> wins{ m_players[0]->get_wins(), m_players[1]->get_wins() };
    m_board.set_scoreboard(names, wins, Player::get_draws());
    int turn{ 0 };
    int row{}, col{};
    char symbol{};
    while (true)
    {
        std::pair<int, int> temp{ get_move(turn) };
        row = temp.first;
        col = temp.second;
        symbol = m_players[turn % 2]->get_symbol();
        m_board.set_cell(row, col, symbol);
        if (m_board.game_over(symbol, row, col))
        {
            break;
        }
        ++turn;
    }
    if (m_board.win(symbol, row, col))
    {
        m_board.set_winner(symbol);
        m_players[turn % 2]->add_win();
    }
    else
    {
        m_board.set_winner('D');
        Player::add_draw();
    }
}
