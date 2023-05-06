#pragma once

#include "Board.h"
#include <fstream>
#include <memory>
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
    explicit Player(char);
    virtual ~Player() = default;

    virtual std::pair<int, int> get_move(Board&) const = 0;

    friend std::ostream& operator<<(std::ostream&, const Player&);

    static std::pair<int, int> convert(int, int);

    const str& get_name() const;
    char get_symbol() const;
    int get_wins() const;
    static int get_draws();
    
    void set_name(const str&);
    void set_wins(int);
    
    void add_win();
    static void add_draw();
    
    void reset_wins();
    static void reset_draws();
};