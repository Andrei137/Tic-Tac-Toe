#pragma once

#include "Exceptions.hpp"
#include <iostream>
#include <string>
#include <utility>

using str = std::string;

class Scoreboard
{
    static Scoreboard* m_instance;
    std::pair<str, str> m_names;
    std::pair<int, int> m_wins;
    int m_draws{};

    Scoreboard() = default;

public:
    Scoreboard(const Scoreboard&) = delete;
    Scoreboard& operator=(const Scoreboard&) = delete;

    static Scoreboard& get_instance();
    void initialize(const std::pair<str, str>&, const std::pair<int, int>&,  int);

    friend std::ostream& operator<<(std::ostream&, const Scoreboard&);
};