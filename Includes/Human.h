#pragma once

#include "Player.h"
#include <Rlutil.h>

class Human : public Player
{
public:
    explicit Human(char);
    std::unique_ptr<Player> clone() const override;
    static int read_input();
    std::pair<int, int> get_move(Board a_board) const override;
};
