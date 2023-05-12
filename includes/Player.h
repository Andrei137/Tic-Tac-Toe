#pragma once

#include "Exceptions.h"
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

    static std::pair<int, int> convert(int, int);

public:
    Player() = default;
    explicit Player(char);
    Player(const Player&);
    Player& operator=(const Player&);
    virtual ~Player() = default;

    friend std::istream& operator>>(std::istream&, const std::shared_ptr<Player>&);
    friend std::ostream& operator<<(std::ostream&, const Player&);

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

    virtual std::pair<int, int> get_move(const Board&) const = 0;
};