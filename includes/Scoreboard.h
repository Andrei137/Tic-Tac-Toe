#pragma once

#include <iostream>
#include <string>
#include <utility>

using str = std::string;

class Scoreboard
{
    std::pair<str, str> m_names;
    std::pair<int, int> m_wins;
    int m_draws{};

public:
    Scoreboard() = default;
    explicit Scoreboard(std::pair<str, str>, std::pair<int, int>, int);
    Scoreboard(const Scoreboard&) = default;
    ~Scoreboard() = default;

    Scoreboard& operator=(const Scoreboard&) = default;

    friend std::ostream& operator<<(std::ostream&, const Scoreboard&);
};