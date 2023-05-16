#include "../includes/Heart.hpp"
#include "../includes/Interface.hpp"
#include <chrono>
#include <sstream>
#include <thread>

Interface* Interface::m_instance{ nullptr };
short Interface::m_size = 3;

Interface& Interface::get_instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Interface();
    }
    return *m_instance;
}

Interface::~Interface()
{
    rlutil::showcursor();
    Heart::print_full_heart();
}

void Interface::destroy_instance()
{
    get_instance().~Interface();
}

template <short Size>
void Interface::start_game(Game<Size>& a_game, players& a_players, char& a_gamemode, char& a_difficulty, bool& a_reseted)
{
    a_game.initialize();
    char gamemode{ a_game.get_gamemode() };
    if (gamemode == '0')
    {
        m_size = 0;
        return;
    }
    int size{ a_game.get_changed_size() };
    if (m_size != size)
    {
        m_size = size;
        a_players[0] = a_players[1] = nullptr;
        a_gamemode = a_difficulty = '?';
        a_reseted = true;
        return;
    }
    a_game.play();
    if (a_game.get_gamemode() == '0')
    {
        m_size = 0;
        return;
    }
    a_game.replay();
    a_players = a_game.get_players();
    a_gamemode = a_game.get_gamemode();
    a_difficulty = a_game.get_difficulty();
    a_reseted = a_game.get_reseted();
}

void Interface::play_tictactoe()
{
    players a_players{ nullptr, nullptr };
    char a_gamemode{'?'};
    char a_difficulty{'?'};
    bool a_reseted{true};
    while (true)
    {
        if (m_size == 0)
        {
            destroy_instance();
            return;
        }
        if (m_size == 3)
        {
            Game<3> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<3>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 4)
        {
            Game<4> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<4>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 5)
        {
            Game<5> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<5>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 6)
        {
            Game<6> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<6>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 7)
        {
            Game<7> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<7>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 8)
        {
            Game<8> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<8>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else if (m_size == 9)
        {
            Game<9> game{a_players, a_gamemode, a_difficulty, a_reseted};
            start_game<9>(game, a_players, a_gamemode, a_difficulty, a_reseted);
        }
        else
        {
            throw initialization_error("Error: The game stopped because the board did not load properly!\n"
                                       "Try restarting the program or contacting the developer\n\n");
        }
    }
}