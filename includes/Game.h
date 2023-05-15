#pragma once

#include "AI.h"
#include "Board.h"
#include "Easy.h"
#include "Hard.h"
#include "Heart.h"
#include "Human.h"
#include "Impossible.h"
#include <array>
#include <ctime>
#include <cstdlib>

class Game
{
    std::array<std::shared_ptr<Player>, 2> m_players{};
    Board m_board{};
    char m_gamemode{};
    char m_difficulty{};
    bool m_reseted{};

    void swap_players();
    void create_AI(int, int, char);

    static void print_logo();
    void print_winner();

    char make_decision(const str&, const str&);
    void initialize();
    void replay();

    std::pair<int, int> get_move(int);
    void play();

    friend std::istream& operator>>(std::istream&, Game&);
    friend std::ostream& operator<<(std::ostream&, const Game&);
    
public:
    Game() = default;
    explicit Game(int);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();

    void tictactoe();
};
