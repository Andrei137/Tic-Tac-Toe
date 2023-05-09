#include "../includes/Heart.h"
#include <cmath>
#include <iostream>
#include <rlutil.h>

#define elif else if

std::array<str, 3> Heart::m_message{"THANK", "  U FOR ", "PLAYING"};

bool Heart::fast_check(float a_x, float a_value1, float a_value2, char a_sign)
{
    if (a_sign == '|')
    {
        return (a_x <= a_value1 || a_x >= a_value2);
    }
    else
    {
        return (a_x > a_value1 && a_x < a_value2);
    }
}

bool Heart::is_inside_heart(float a_x, float a_y)
{
    return (a_x * a_x + pow(5.0 * a_y / 4.0 - sqrt(fabs(a_x)), 2) - 1 <= 0.0);
}

void Heart::print_heart(float a_x, float a_y, bool a_condition)
{
    rlutil::setColor(4);
    if (is_inside_heart(a_x, a_y) && a_condition)
    {
        std::cout << "*";
    }
    else
    {
        std::cout << " ";
    }
}

void Heart::print_message(float a_x, float a_y, bool a_condition, int a_i, int& a_j)
{
    if (is_inside_heart(a_x, a_y))
    {
        if (fast_check(a_x, -0.33f, 0.33f, '|'))
        {
            rlutil::setColor(4);
            std::cout << '*';
        }
        elif (a_condition)
        {
            rlutil::setColor(4);
            std::cout << " ";
        }
        else
        {
            rlutil::setColor(7);
            std::cout << m_message[a_i][a_j++];
        }
    }
    else
    {
        std::cout << " ";
    }
}

void Heart::for_heart(float a_y, int a_condition)
{
    for (float i = -1.1f; i <= 1.1f; i += 0.025f)
    {
        if (a_condition == 1)
        {
            print_heart(i, a_y, fast_check(i, -0.33f, 0.33f, '|'));
        }
        else
        {
            print_heart(i, a_y, true);
        }
    }
}

void Heart::for_message(float a_y, int a_condition)
{
    int k1 = 0, k2 = 0, k3 = 0;
    for (float i = -1.1f; i <= 1.1f; i += 0.025f)
    {
        if (a_condition == 1)
        {
            print_message(i, a_y, fast_check(i, -0.06f, 0.06f, '|'), 0, k1);
        }
        elif (a_condition == 2)
        {
            print_message(i, a_y, fast_check(i, -0.12f, 0.12f, '|'), 1, k2);
        }
        else
        {
            print_message(i, a_y, fast_check(i, -0.08f, 0.08f, '|'), 2, k3);
        }
    }
}

void Heart::print_full_heart()
{
    for (float y = 1.3f; y >= -0.7f; y -= 0.06f)
    {
        if (fast_check(y, 0.5f, 0.55f, '&'))
        {
            for_message(y, 1);
        }
        elif (fast_check(y, 0.4f, 0.45f, '&'))
        {
            for_message(y, 2);
        }
        elif (fast_check(y, 0.25f, 0.3f, '&'))
        {
            for_message(y, 3);
        }
        elif (fast_check(y, 0.2f, 0.6f, '&'))
        {
            for_heart(y, 1);
        }
        else
        {
            for_heart(y, 2);
        }
        std::cout << '\n';
    }
    rlutil::setColor(7);
    rlutil::msleep(50);
    rlutil::locate(0, 0);
    std::cout << '\n';
}
