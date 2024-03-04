#pragma once

#include "AIFactory.hpp"
#include "Board.hpp"
#include "Human.hpp"
#include <array>

using players = std::array<std::shared_ptr<Player>, 2>;

template <short Size>
class Game
{
    players m_players{};
    Board m_board{};
    char m_gamemode{};
    char m_difficulty{};
    bool m_reseted{};
    short m_changed_size{};

    void create_AI(int, int, char);
    std::pair<int, int> get_move(int);
    char make_decision(const str&, const str&);

    template <short GameSize>
    friend std::istream& operator>>(std::istream&, Game<GameSize>&);

    template <short GameSize>
    friend std::ostream& operator<<(std::ostream&, const Game<GameSize>&);
    
public:
    explicit Game(players, char, char, bool);
    Game(const Game&);
    Game& operator=(const Game&);
    ~Game() = default;

    void set_difficulty(char);
    void set_gamemode(char);

    players get_players() const;
    char get_gamemode() const;
    char get_difficulty() const;
    bool get_reseted() const;
    short get_changed_size() const;

    void print_logo();
    void print_winner();
    void swap_players();
    void initialize();
    void replay();
    void play();
};

#include "../sources/Game.tpp"