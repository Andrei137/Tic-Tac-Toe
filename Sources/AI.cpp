#include "../Includes/AI.h"

AI::AI(char a_symbol) : Player(a_symbol)
{
    this->set_name("Computer");
}

AI& AI::operator=(const AI& a_other)
{
    if (this == &a_other)
    {
        return *this;
    }
    AI::operator=(a_other);
    return *this;
}
