#include "Board.h"
#include "Player.h"

#include <chrono>
#include <thread>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
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

    str get_input_string_with_timeout(int timeout);
    std::pair<int, int> convert(int);
    void move(int);
    void play();
};
