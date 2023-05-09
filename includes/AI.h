#pragma once

#include "Player.h"
#include <ctime>
#include <cstdlib>

class AI : public Player
{
protected:
    explicit AI(char);
    AI(const AI&) = default;
    AI& operator=(const AI&);
    ~AI() override = default;

    void loading(const Board&) const;
    std::pair<int, int> get_move(const Board&) const override = 0;
};