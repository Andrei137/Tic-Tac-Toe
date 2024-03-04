#pragma once

#include "AI.hpp"

class AIFactory
{
public:
    static std::shared_ptr<Player> easy(char);
    static std::shared_ptr<Player> hard(char);
    static std::shared_ptr<Player> impossible(char);
};
