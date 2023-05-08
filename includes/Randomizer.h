#include "AI.h"
#include <ctime>
#include <cstdlib>

class Randomizer : public AI
{
public:
    explicit Randomizer(char);
    Randomizer(const Randomizer&) = default;
    Randomizer& operator=(const Randomizer&);
    ~Randomizer() override = default;

    std::pair<int, int> get_move(Board& a_board) const override;
};
