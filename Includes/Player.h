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
    Player(char a_symbol, const str& a_name = "Unknown");
    Player(const Player& a_other);
    Player& operator=(const Player& other);
    ~Player();

    friend std::ostream& operator<<(std::ostream& a_out, const Player& a_player);

    const str& get_name() const;
    char get_symbol() const;
    int get_wins() const;
    static int get_draws();

    void set_name(const str& a_name);
    void set_symbol(char a_symbol);
    void add_win();
    static void add_draw();
    static void reset_draws();
};