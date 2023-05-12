#pragma once

#include "Board.h"
#include "Heart.h"
#include "Human.h"
#include "Randomizer.h"
#include "Solver.h"
#include "StickyNoob.h"
#include <array>

class Game
{
    std::array<std::shared_ptr<Player>, 2> m_players{};
    Board m_board{};
    char m_gamemode{};
    char m_difficulty{};
    bool m_reseted{};

    void swap_players();
    static void print_logo();
    void print_winner();
    char make_decision(const str&, const str&);
    void initialize();
    std::pair<int, int> get_move(int);
    void play();
    void replay();

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
