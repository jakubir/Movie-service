#include "Utils.h"

bool readInt(int& value)
{
    if (!(std::cin >> value)) // validate if input is an integer
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}