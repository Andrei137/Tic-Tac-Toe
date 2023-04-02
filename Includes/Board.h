#pragma once

#include "Square.h"
#include <iostream>
#include <string>

class Board
{
    int m_size{};
    Square** m_cells{};
    char m_winner{};

    void allocate_memory();
    void deallocate_memory();

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
    ~Board();

    Board& operator=(const Board&);

    friend std::ostream& operator<<(std::ostream&, const Board&);

    int get_size() const;
    Square get_cell(int, int) const;
    [[maybe_unused]] char get_winner() const;

    void set_cell(int, int, char);
    [[maybe_unused]] void set_winner(char);

    bool valid_move(int, int) const;
    bool win(char) const;
    bool draw() const;
    bool game_over() const;
};