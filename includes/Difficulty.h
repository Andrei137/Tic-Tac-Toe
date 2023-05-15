#pragma once

#include "Board.h"
#include <rlutil.h>

class Difficulty 
{
protected:
    void loading(const Board&) const;

    static std::pair<int, int> convert(int, int);

public:
    Difficulty() = default;
    virtual Difficulty* clone() const = 0;
    Difficulty(const Difficulty&) = default;
    Difficulty& operator=(const Difficulty&);
    virtual ~Difficulty() = default;
    virtual std::pair<int, int> get_move(const Board& board, char) const = 0;

};