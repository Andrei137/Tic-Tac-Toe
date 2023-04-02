#include "Board.h"
#include "Player.h"

#include <chrono>
#include <thread>

#ifdef _WIN32
#define CTRL(c) ((c) & 037)
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

class Game
{
    Player m_player1{'X'};
    Player m_player2{'O'};
    Board m_board{};
    
public:
    Game() = default;
    explicit Game(int);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game() = default;
    
    friend std::istream& operator>>(std::istream&, Game&);
    friend std::ostream& operator<<(std::ostream&, const Game&);
    
    static str get_input(int);
    std::pair<int, int> convert(int);
    void move(int);
    void play();
};
