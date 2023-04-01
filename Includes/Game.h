#include "Board.h"
#include "Player.h"

class Game
{
    Player m_player1{'X'};
    Player m_player2{'O'};
    Board m_board{};

public:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game() = default;

    void play();
};
