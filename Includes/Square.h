#pragma once

#include <fstream>
#include <string>

typedef std::string str;

class Square
{
    char m_value{};
    str m_free_pos{};
    bool m_occupied{};

public:
    Square() = default;
    explicit Square(char, const str&, bool);
    ~Square() = default;

    friend std::ostream& operator<<(std::ostream&, const Square&);

    char get_value() const;
    str get_free_pos() const;
    bool is_occupied() const;

    void set_value(char);
    void set_free_pos(const str&);
    void set_occupied(bool);
};