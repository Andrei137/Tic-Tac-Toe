#pragma once
#include <string>

using str = std::string;

class Square
{
    char m_value{};
    bool m_occupied{};
    
public:
    Square() = default;
    explicit Square(char, bool);
    Square(const Square&);
    ~Square() = default;

    Square& operator=(const Square&);
    
    char get_value() const;
    bool is_occupied() const;
    
    void set_value(char);
    void set_occupied(bool);
};