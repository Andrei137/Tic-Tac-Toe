#include "includes/Interface.hpp"

int main()
{
    bool play{ true };
    int attempts{ 0 };
    while (play)
    {
        ++attempts;
        play = false;
        try
        {
            Interface::play_tictactoe();
        }
        catch (initialization_error& err)
        {
            rlutil::cls();
            std::cerr << err.what();
        }
        catch (timeout_error& err)
        {
            rlutil::cls();
            std::cerr << err.what();
        }
        catch (excessive_attempts_error& err)
        {
            std::cerr << err.what();
            rlutil::msleep(4000);
            rlutil::cls();
            std::cout << "Fine, I'll give you one more chance!\n";
            std::cout << "This time try not to break anything\n";
            std::cout << "Press any key to continue...";
            rlutil::anykey();
            if (attempts < 5)
            {
                play = true;
            }
            else
            {
                rlutil::cls();
            }
        }
        catch (...)
        {
            std::cerr << "Something went wrong... ):\n\n";
        }
    }
    return 0;
}