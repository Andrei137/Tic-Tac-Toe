#pragma once

#include "AI.h"

class StickyNoob : public AI
{
public:
    explicit StickyNoob(char);
    StickyNoob(const StickyNoob&) = default;
    StickyNoob& operator=(const StickyNoob&);
    ~StickyNoob() override = default;

    std::pair<int, int> get_move(const Board&) const override;
};
