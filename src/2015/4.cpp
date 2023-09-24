#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

bool noOverlap (std::string input);

bool atLeastOnLetterBetweenTwoSameLetters (std::string input);

// TODO: revisit and see why this solution doesn't work
int
main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    std::fstream inFile (argv[1]);
    if (!inFile)
    {
        std::cout << "Couldn't open file" << std::endl;
        return 2;
    }

    int niceCount = 0;
    std::string buff;
    while (getline (inFile, buff))
    {
        if (noOverlap (buff) && atLeastOnLetterBetweenTwoSameLetters (buff))
            niceCount++;
    }

    std::cout << niceCount << std::endl;

    return 0;
}

bool
noOverlap (std::string input)
{
    std::unordered_map<std::string, std::pair<int, int>> beginningIndices ({});
    for (size_t i = 0; i <= input.length () - 2; i++)
    {
        std::string window = input.substr (i, 2);
        if (beginningIndices.find (window) != beginningIndices.end ())
        {
            if (i - beginningIndices[window].first < 2)
                return false;
            else
            {
                beginningIndices[window].first = i;
                beginningIndices[window].second++;
            }
        }
        else
            beginningIndices[window] = { i, 1 };
    }

    for (auto i = beginningIndices.begin (); i != beginningIndices.end (); i++)
    {
        if (i->second.second >= 2)
            return true;
    }

    return false;
}

bool
atLeastOnLetterBetweenTwoSameLetters (std::string input)
{
    for (size_t j = 2, i = 0; j < input.length (); j++, i++)
    {
        if (input[j] == input[i])
            return true;
    }

    return false;
}