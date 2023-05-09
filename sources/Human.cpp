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
                throw NotNumberException();
            }
            else if (temp.size() > 3)
            {
                throw OutOfBoundsCellException();
            }
            index = std::stoi(temp);
            valid = true;
        }
        catch (NotNumberException const& err)
        {
            rlutil::cls();
            std::cout << err.what();
            rlutil::msleep(2000);
            rlutil::cls();
        }
        catch (OutOfBoundsCellException const& err)
        {
            rlutil::cls();
            std::cout << err.what();
            rlutil::msleep(2000);
            rlutil::cls();
        }
    }
    return convert(index, a_board.get_size());
}
