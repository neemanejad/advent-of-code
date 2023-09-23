#include <fstream>
#include <iostream>
#include <unordered_set>

struct hashFunction
{
    size_t
    operator() (const std::pair<int, int> &x) const
    {
        return x.first ^ x.second;
    }
};

int
main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    std::unordered_set<std::pair<int, int>, hashFunction> houses (
        { { 0, 0 } });
    std::ifstream inFile (argv[1]);

    if (!inFile)
    {
        std::cout << "Couldn't open file" << std::endl;
        return 2;
    }

    std::string buff;
    inFile >> buff;

    std::pair<int, int> santaCoord = { 0, 0 };
    std::pair<int, int> robotCoord = { 0, 0 };
    auto current = &robotCoord;
    for (auto dir : buff)
    {
        current = *current == robotCoord ? &santaCoord : &robotCoord;
        std::pair<int, int> newCoord = *current;

        switch (dir)
        {
        case '^':
            newCoord.second++;
            break;
        case '>':
            newCoord.first++;
            break;
        case 'v':
            newCoord.second--;
            break;
        case '<':
            newCoord.first--;
            break;
        }

        houses.insert (newCoord);

        *current = newCoord;
    }

    std::cout << houses.size () << std::endl;

    return 0;
}
