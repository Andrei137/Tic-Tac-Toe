#pragma once

#include "Square.h"
#include <iostream>
#include <string>
#include <vector>

class Board
{
    int m_size{};
    std::vector<std::vector<Square>> m_cells{};
    char m_winner{};
    
    static short nr_digits(int);
    
    template <typename T>
    void display_aux(const str&, const str&, const T*, bool) const;
    
    void display_1() const;
    void display_2(int) const;
    void display_3() const;
    
    
public:
    Board() = default;
    explicit Board(int);
    Board(const Board&);
    ~Board() = default;
    
    Board& operator=(const Board&);
    
    friend std::ostream& operator<<(std::ostream&, const Board&);
    
    int get_size() const;
    char get_winner() const;
    
    void set_cell(int, int, char);
    void set_winner(char);

    void reset();
    bool valid_move(int, int) const;
    bool win_col(char, int, int) const;
    bool win_row(char, int, int) const;
    bool win_diag1(char, int, int) const; 
    bool win_diag2(char, int, int) const;
    bool win(char, int, int) const;
    bool draw() const;
    bool game_over(char, int, int) const;
};