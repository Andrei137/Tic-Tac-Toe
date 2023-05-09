#pragma once

#include <stdexcept>

using str = std::string;

class MoveException : public std::runtime_error
{
public:
    explicit MoveException(const str& a_msg) : std::runtime_error(a_msg) {}
};

class NotNumberException : public MoveException
{
public:
    NotNumberException() : MoveException("Invalid input. Please choose a number!") {}
};

class OutOfBoundsCellException : public MoveException
{
public:
    OutOfBoundsCellException() : MoveException("Invalid input. Please choose a cell within the board!") {}
};

class NonEmptyCellException : public MoveException
{
public:
    NonEmptyCellException() : MoveException("Invalid move. Please choose an empty cell!") {}
};

class InputException : public std::runtime_error
{
public:
    explicit InputException(const str& a_msg) : std::runtime_error(a_msg) {}
};

class NumberOfPlayersInputException : public InputException
{
public:
    NumberOfPlayersInputException() : InputException("Invalid input. Please choose 1 or 2 players or exit de program!") {}
};

class DifficultyInputException : public InputException
{
public:
    DifficultyInputException() : InputException("Invalid input. Please choose a valid difficulty option!") {}
};

class NameInputException : public InputException
{
public:
    NameInputException() : InputException("Invalid input. Name must be between 1 and 20 characters and only contain letters, numbers, and special characters.") {}
};

class ReplayInputException : public InputException
{
public:
    ReplayInputException() : InputException("Invalid input. Please choose 'y' or 'n'!") {}
};
