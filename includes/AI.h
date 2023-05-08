#pragma once

#include "Player.h"

class AI : public Player
{
protected:
    explicit AI(char);
    AI(const AI&) = default;
    AI& operator=(const AI&);
    ~AI() override = default;

    std::pair<int, int> get_move(Board&) const override  = 0;
};