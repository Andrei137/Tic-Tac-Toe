#pragma once

#include "Board.hpp"
#include "Difficulty.hpp"
#include <memory>
#include <rlutil.h>
#include <string>

using str = std::string;

class Player
{
protected:
    char m_symbol{};
    str m_name{};
    int m_wins{};
    static int m_draws;
    std::shared_ptr<Difficulty> m_difficulty{};

    static std::pair<int, int> convert(int, int);

public:
    explicit Player(char);
    virtual Player* clone() const = 0;
    Player(const Player&);
    Player& operator=(const Player&);
    virtual ~Player() = default;

    friend std::istream& operator>>(std::istream&, const std::shared_ptr<Player>&);
    friend std::ostream& operator<<(std::ostream&, const Player&);

    static str get_input(std::istream&);
    static void handle_wrong_input(short&, const str&);

    const str& get_name() const;
    char get_symbol() const;
    int get_wins() const;
    static int get_draws();

    void set_symbol(const char&);
    void set_name(const str&);

    void add_win();
    static void add_draw();
    static void reset_draws();

    virtual void set_difficulty(std::shared_ptr<Difficulty>) = 0;
    virtual std::pair<int, int> get_move(const Board&) const = 0;
};