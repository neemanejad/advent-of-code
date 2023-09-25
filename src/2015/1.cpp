#include <fstream>
#include <iostream>
#include <string.h>

int
main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    std::fstream inFile (argv[1]);
    std::string input;
    inFile >> input;

    int result = 0;
    int index = 0;

    for (size_t i = 0; i < input.length (); i++)
    {
        if (input[i] == '(')
            result++;
        else
            result--;

        if (result == -1)
        {
            index = i + 1;
            break;
        }
    }

    std::cout << index << std::endl;

    return 0;
}