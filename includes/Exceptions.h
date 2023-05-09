#pragma once

#include <stdexcept>

using str = std::string;

class invalid_move_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class not_number_error : public invalid_move_error
{
public:
    not_number_error() : invalid_move_error("Invalid input. Please choose a number!") {}
};

class out_of_bound_error : public invalid_move_error
{
public:
    out_of_bound_error() : invalid_move_error("Invalid input. Please choose a cell within the board!") {}
};

class non_empty_cell_error : public invalid_move_error
{
public:
    non_empty_cell_error() : invalid_move_error("Invalid move. Please choose an empty cell!") {}
};

class input_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class number_of_players_error : public input_error
{
public:
    number_of_players_error() : input_error("Invalid input. Please choose 1 or 2 players or select \"Exit\"!") {}
};

class difficulty_error : public input_error
{
public:
    difficulty_error() : input_error("Invalid input. Please choose a valid difficulty option or select \"Go Back\"!") {}
};

class name_error : public input_error
{
public:
    name_error() : input_error("Invalid input. Name must be between 1 and 20 characters and only contain letters, numbers, and special characters.") {}
};

class replay_error : public input_error
{
public:
    replay_error() : input_error("Invalid input. Please choose 'y' or 'n'!") {}
};
