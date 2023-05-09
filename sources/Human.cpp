#include "../includes/Human.h"
#include <regex>

Human::Human(char a_symbol) : Player(a_symbol) 
{
    this->set_name("Unknown");
}

Human& Human::operator=(const Human& a_other)
{
    if (this != &a_other) 
    {
        Player::operator=(a_other);
    }
    return *this;
}

std::pair<int, int> Human::get_move(const Board& a_board) const
{
    std::regex digits(R"(^-?[0-9]{1,20}$)"); 
    bool valid{ false };
    int index{};
    while (!valid)
    {
        try
        {
            rlutil::cls();
            std::cout << a_board;
            rlutil::showcursor();
            std::cout << *this;
            str temp{};
            std::cin >> temp;
            if (!std::regex_match(temp, digits))
            {
                throw not_number_error();
            }
            else if (temp.size() > 3)
            {
                throw out_of_bound_error();
            }
            if (temp == "0")
            {
                return {-1, -1};
            }
            index = std::stoi(temp);
            valid = true;
        }
        catch (not_number_error const& err)
        {
            rlutil::hidecursor();
            rlutil::cls();
            std::cout << err.what();
            rlutil::msleep(2000);
        }
        catch (out_of_bound_error const& err)
        {
            rlutil::hidecursor();
            rlutil::cls();
            std::cout << err.what();
            rlutil::msleep(2000);
        }
    }
    return convert(index, a_board.get_size());
}
