#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

struct Dimensions
{
    int l;
    int w;
    int h;
};

int
main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    std::string buff;
    std::ifstream file (argv[1]);

    if (!file)
    {
        std::cout << "Failed to open file" << std::endl;
        return 2;
    }

    int wrappingTotal = 0;
    int ribbonTotal = 0;
    while (std::getline (file, buff))
    {
        if (buff == "")
            continue;

        int l, w, h, li, wi;

        li = buff.find ('x');
        l = atoi (buff.substr (0, li).c_str ());

        wi = buff.find ('x', li + 1);
        w = atoi (buff.substr (li + 1, wi).c_str ());

        h = atoi (buff.substr (wi + 1).c_str ());

        int area = (2 * l * w) + (2 * l * h) + (2 * h * w);
        int extra = std::min ({ l * h, w * h, w * l });
        int ribbon
            = std::min ({ 2 * l + 2 * h, 2 * l + 2 * w, 2 * w + 2 * h });

        wrappingTotal += area + extra;
        ribbonTotal += ribbon + (l * h * w);
    }

    std::cout << "Wrapping total:" << wrappingTotal << std::endl;
    std::cout << "Ribbon total:" << ribbonTotal << std::endl;

    return 0;
}
