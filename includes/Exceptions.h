#pragma once

#include <stdexcept>

using str = std::string;

class execution_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class excessive_attempts_error : public execution_error
{
public:
    excessive_attempts_error() : execution_error{"C'mon, you maniac. Is it really that hard not to try to break everything?!"} {}
};

class timeout_error : public execution_error
{
public:
    timeout_error() : execution_error{"Detected user inactivity! The program will stop now in order to free your RAM!\nFeel free to play again!\n\n"} {}
};

class initialization_error : public execution_error
{
public:
    explicit initialization_error(const str& a_message) 
        : execution_error(str("Error: The game stopped because the ") + a_message + " did not load properly!\n"
                          "Try restarting the program or contacting the developer\n\n") {}
};