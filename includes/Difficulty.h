#pragma once

#include "Board.h"

class Difficulty 
{
public:
    virtual Difficulty* clone() const = 0;
    virtual ~Difficulty() = default;

    virtual int get_move(const Board& board, char) const = 0;
};