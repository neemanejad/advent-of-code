#include <fstream>
#include <iostream>
#include <unordered_set>

bool atLeastThreeVowels (std::string input);

bool letterTwiceInARow (std::string input);

bool doesNotContainStrings (std::string input);

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
        if (atLeastThreeVowels (buff) && doesNotContainStrings (buff)
            && letterTwiceInARow (buff))
            niceCount++;
    }

    std::cout << niceCount << std::endl;

    return 0;
}

bool
atLeastThreeVowels (std::string input)
{
    int count = 0;
    std::unordered_set<char> vowels ({ 'a', 'e', 'i', 'o', 'u' });
    for (auto c : input)
    {
        if (vowels.find (c) != vowels.end ())
            count++;
    }

    return count >= 3;
}

bool
letterTwiceInARow (std::string input)
{
    for (size_t j = 1, i = 0; j < input.length (); j++, i++)
    {
        if (input[j] == input[i])
            return true;
    }

    return false;
}

bool
doesNotContainStrings (std::string input)
{
    std::unordered_set<std::string> words ({ "ab", "cd", "pq", "xy" });
    for (size_t i = 0; i <= input.length () - 2; i++)
    {
        std::string window = input.substr (i, 2);
        if (words.find (window) != words.end ())
            return false;
    }

    return true;
}