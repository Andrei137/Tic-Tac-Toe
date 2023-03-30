#include "Includes\Player.h"
#include <fstream>

int main() 
{
    std::ofstream out("Players.txt");

    Player p1{'X', "Alice"};
    Player p2{'O'};
    p1.add_win();
    Player::add_draw();
    p2.add_win();
    p2.add_win();
    out << p1 << '\n';
    out << p2 << '\n';
    out.close();
    return 0;
}