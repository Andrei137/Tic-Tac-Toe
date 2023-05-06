#include "Board.h"
#include "Player.h"
#include <array>

class Game
{
    std::array<Player*, 2> m_players{};
    Board m_board{};
    char m_gamemode{};
    
public:
    Game() = default;
    explicit Game(int);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();
    
    friend std::istream& operator>>(std::istream&, Game&);
    friend std::ostream& operator<<(std::ostream&, const Game&);

    int read_input(int, int);
    std::pair<int, int> convert(int);
    void move(int, int&, int&);
    void print_logo();
    void play(bool);
};
