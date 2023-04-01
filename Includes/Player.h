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

    [[maybe_unused]] void set_name(const str&);
    [[maybe_unused]] void set_symbol(char);
    
    [[maybe_unused]] void add_win();
    [[maybe_unused]] static void add_draw();
    [[maybe_unused]] static void reset_draws();
};