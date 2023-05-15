#pragma once

#include "Player.h"
#include "Difficulty.h"

class AI : public Player
{
public:
    explicit AI(char);
    AI* clone() const override;
    ~AI() override = default;

    
    void set_difficulty(std::shared_ptr<Difficulty>) override;

    std::pair<int, int> get_move(const Board&) const override;
};