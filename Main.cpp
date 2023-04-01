#include "Includes/Board.h"

int main() 
{
    Board b{3};
    b.set_cell(0, 0, 'X');
    b.set_cell(1, 1, 'O');
    std::cout << b << '\n';
    Board c{4};
    c.set_cell(2, 2, 'X');
    std::cout << c << '\n';
    Board d{10};
    d.set_cell(8, 9, 'X');
    std::cout << d << '\n';
    return 0;
}