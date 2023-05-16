#include "includes/Interface.hpp"

int main()
{
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
        std::cout << "Fine, I'll give you one last chance!\n";
        std::cout << "This time try not to break anything\n";
        std::cout << "Press any key to continue...";
        rlutil::anykey();
        try
        {
            Interface::play_tictactoe();
        }
        catch(initialization_error& second_err)
        {
            rlutil::cls();
            std::cerr << second_err.what();
        }
        catch(...)
        {
            rlutil::cls();
            std::cerr << "No more chances for you! ):\n\n";
        }
    }
    catch (...)
    {
        std::cerr << "Something went wrong... ):\n\n";
    }
    return 0;
}
