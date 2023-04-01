#include "Includes/Board.h"
#include <ctime>
#include <cstdlib>

const int SIZE{ 3 };

int main() 
{
    Board b{SIZE};
    int turn{1};
    srand(time(nullptr));
    while (!b.game_over())
    {
        int x{ rand() % SIZE }, y{ rand() % SIZE };
        while (!b.valid_move(x, y))
        {
            x = rand() % SIZE;
            y = rand() % SIZE;
        }
        b.set_cell(x, y, turn % 2 ? 'X' : 'O');
        turn++;
        std::cout << b << '\n';
    }
    return 0;
}