#pragma once

#include "Player.h"
#include <Rlutil.h>

class Human : public Player
{
public:
    explicit Human(char);
    
    static int read_input();
    std::pair<int, int> get_move(Board a_board) const override;
};
