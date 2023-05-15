#pragma once

#include "Exceptions.h"
#include <iostream>
#include <string>
#include <utility>

using str = std::string;

class Scoreboard
{
    std::pair<str, str> m_names;
    std::pair<int, int> m_wins;
    int m_draws{};

    Scoreboard() = default;

public:
    explicit Scoreboard(std::pair<str, str>, std::pair<int, int>, int);
    Scoreboard(const Scoreboard&) = delete;
    Scoreboard& operator=(const Scoreboard&) = delete;

    static Scoreboard& get_instance();
    void initialize(const std::pair<str, str>&, const std::pair<int, int>&,  int);

    friend std::ostream& operator<<(std::ostream&, const Scoreboard&);
};