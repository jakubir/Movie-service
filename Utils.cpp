#include "Utils.h"

bool readIndex(int& value)
{
    if (!(std::cin >> value)) // validate input is an integer
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}