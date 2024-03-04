#pragma once

#include "Board.hpp"
#include "Minimax.hpp"
#include <rlutil.h>

class Difficulty 
{
public:
    virtual Difficulty* clone() const = 0;
    virtual ~Difficulty() = default;

    virtual int get_move(Board& board, char) = 0;
};