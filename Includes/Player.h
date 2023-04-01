#pragma once

#include <fstream>
#include <string>

typedef std::string str;

class Player 
{
    char m_symbol{};
    str m_name{};
    int m_wins{};
    static int m_draws;

public:
    Player() = default;
    explicit Player(char, str);
    ~Player() = default;

    friend std::ostream& operator<<(std::ostream&, const Player&);

    const str& get_name() const;
    char get_symbol() const;
    int get_wins() const;
    static int get_draws();

    void set_name(const str&);
    void set_symbol(char);
    
    void add_win();
    static void add_draw();
    static void reset_draws();
};