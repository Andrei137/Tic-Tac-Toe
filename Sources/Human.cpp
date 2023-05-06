#include "../Includes/Human.h"

Human::Human(char a_symbol) : Player(a_symbol) {}

/*
int Human::read_input()
{
    str num{};
    time_t start{}, end{};
    bool started{ false };
    while (true) 
    {
        if (kbhit()) 
        {
            char c = getch();
            if (isdigit(c)) 
            {
                if (!started) 
                {
                    time(&start);
                    started = true;
                }
                num += c;
                if (num.size() > 5) 
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
        else 
        {
            time(&end);
            if (num.size() > 5)
            {
                return -1;
            }
        }
        if (started) 
        {
            time(&end);
            double diff = difftime(end, start);
            if (diff >= 1) 
            {
                break;
            }
        }
    }
    int n{ 0 };
    for (const auto& ch : num) 
    {
        n = n * 10 + (ch - '0');
    }
    return n;
}
*/

std::pair<int, int> Human::get_move(Board& a_board) const
{
    rlutil::hidecursor();
    str temp_player{};
    std::cout << "\n-> (" << m_symbol << ") " << m_name << "\'";
    if (m_name[m_name.size() - 1] != 's')
    {
        std::cout << 's';
    }
    std::cout << " Turn : ";
    int invalid_moves{ 0 };
    int row{ -1 }, col{ -1 };
    while (row == -1 && col == -1)
    {
        int index{};
        std::cin >> index;
        if (index == 0 || invalid_moves == 10)
        {
            rlutil::cls();
            a_board.set_winner(' ');
            return { -1, -1 };
        }
        else if (index > a_board.get_size() * a_board.get_size() || index < 1)
        {
            ++invalid_moves;
            row = col = -1;
            continue;
        }
        std::pair<int, int> temp{ convert(index, a_board.get_size()) };
        row = temp.first;
        col = temp.second;
        if (!a_board.valid_move(row, col))
        {
            ++invalid_moves;
            row = col = -1;
        }
    }
    return { row, col };
}
