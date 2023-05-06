#pragma once

#include "Player.h"
#include <Rlutil.h>

class Human : public Player
{
public:
    explicit Human(char);
    Human(const Human&) = default;
    Human& operator=(const Human&);
    ~Human() override = default;

    [[maybe_unused]] static int read_input();
    std::pair<int, int> get_move(Board& a_board) const override;
};
