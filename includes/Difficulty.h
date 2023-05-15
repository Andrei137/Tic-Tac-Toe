#pragma once

#include "Board.h"
#include "Minimax.h"

class Difficulty 
{
public:
    virtual Difficulty* clone() const = 0;
    virtual ~Difficulty() = default;

    virtual int get_move(Board& board, char) = 0;
};