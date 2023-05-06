#pragma once

#include "Board.h"
#include "Human.h"
#include <array>

class Game
{
    std::array<std::unique_ptr<Player>, 2> m_players{};
    Board m_board{};
    char m_gamemode{};
    bool m_reseted{};
    
public:
    Game() = default;
    explicit Game(int);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();
    
    friend std::istream& operator>>(std::istream&, Game&);
    friend std::ostream& operator<<(std::ostream&, const Game&);

    void swap_players();
    static void print_logo();
    static std::pair<int, int> move(int a_turn, Board&, std::array<std::unique_ptr<Player>, 2>&);
    void play();
};
