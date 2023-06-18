#include "Game.hpp"

class Interface
{
    static Interface *m_instance;
    static short m_size;

    Interface() = default;

    static void destroy_instance();

public:
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    static Interface& get_instance();
    ~Interface() = default;

    template <short Size>
    static void start_game(Game<Size>&, players&, char&, char&, bool&);
    static void play_tictactoe();
};