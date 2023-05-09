#pragma once

#include "Board.h"
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

public:
    Player() = default;
    explicit Player(char);
    Player(const Player&);
    Player& operator=(const Player&);
    virtual ~Player() = default;

    friend std::ostream& operator<<(std::ostream&, const Player&);

    static std::pair<int, int> convert(int, int);
    virtual std::pair<int, int> get_move(const Board&) const = 0;

    const str& get_name() const;
    char get_symbol() const;
    int get_wins() const;
    static int get_draws();
    
    void set_symbol(const char&);
    void set_name(const str&);

    void add_win();
    static void add_draw();
    
    void reset_wins();
    static void reset_draws();
};