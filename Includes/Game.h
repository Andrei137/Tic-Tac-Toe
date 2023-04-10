#include "Board.h"
#include "Player.h"

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

    int read_input(int, int);
    std::pair<int, int> convert(int);
    void move(int, int&, int&);
    void play();
};
