#pragma once

#include "Player.hpp"

class Human : public Player
{
public:
    explicit Human(char);
    Human* clone() const override;
    Human(const Human&);
    Human& operator=(const Human&);
    ~Human() override = default;

    void set_difficulty(std::shared_ptr<Difficulty>) override;

    std::pair<int, int> get_move(const Board&) const override;
};