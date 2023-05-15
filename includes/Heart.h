#pragma once

#include <array>
#include <string>

using str = std::string;

class Heart
{
    static Heart* m_instance;
    static std::array<str, 3> m_message;

    Heart() = default;

    static bool fast_check(float, float, float, char);
    static bool is_inside_heart(float, float);
    static void print_heart(float, float, bool);
    static void print_message(float, float, bool, int, int&);
    static void for_heart(float, int);
    static void for_message(float, int);

public:
    Heart(const Heart&) = delete;
    Heart& operator=(const Heart&) = delete;
    static Heart& get_instance();

    static void print_full_heart();
};