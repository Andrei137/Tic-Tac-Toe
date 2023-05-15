#include "../includes/AIFactory.h"
#include "../includes/Easy.h"
#include "../includes/Hard.h"
#include "../includes/Impossible.h"

std::shared_ptr<Player> AIFactory::easy(char a_symbol)
{
    std::shared_ptr<Player> ai{ std::make_shared<AI>(a_symbol) };
    std::shared_ptr<Difficulty> difficulty{ std::make_shared<Easy>() };
    ai->set_difficulty(std::move(difficulty));
    ai->set_name("Computer (Easy)");
    return ai;
}

std::shared_ptr<Player> AIFactory::hard(char a_symbol)
{
    std::shared_ptr<Player> ai{ std::make_shared<AI>(a_symbol) };
    std::shared_ptr<Difficulty> difficulty{ std::make_shared<Hard>() };
    ai->set_difficulty(std::move(difficulty));
    ai->set_name("Computer (Hard)");
    return ai;
}

std::shared_ptr<Player> AIFactory::impossible(char a_symbol)
{
    std::shared_ptr<Player> ai{ std::make_shared<AI>(a_symbol) };
    std::shared_ptr<Difficulty> difficulty{ std::make_shared<Impossible>() };
    ai->set_difficulty(std::move(difficulty));
    ai->set_name("Computer (Impossible)");
    return ai;
}