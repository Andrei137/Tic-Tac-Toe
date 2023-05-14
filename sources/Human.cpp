#include "../includes/Human.h"
#include <regex>

Human::Human(char a_symbol) : Player(a_symbol) 
{
    this->set_name("Unknown");
}

Human* Human::clone() const
{
    return new Human(*this);
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
    short wrong_inputs{ 0 };
    while (true)
    {
        rlutil::showcursor();
        if (wrong_inputs == 10)
        {
            throw excessive_attempts_error();
        }
        std::cout << a_board;
        std::cout << *this;
        str temp{ get_input(std::cin) };
        if (!std::regex_match(temp, digits))
        {
            handle_wrong_input(wrong_inputs, "Invalid input. Please choose a number!");
            continue;
        }
        if (temp == "0")
        {
            return {-1, -1};
        }
        int index{ std::stoi(temp) };
        return convert(index, a_board.get_size());
    }
}
