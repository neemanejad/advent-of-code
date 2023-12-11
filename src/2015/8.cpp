#include <fstream>
#include <iostream>
#include <string>

int
main (void)
{
    std::fstream inputFile ("../input/8-input.txt");

    if (!inputFile)
    {
        throw new std::invalid_argument ("Input file doesn't exist");
    }

    size_t charCounter = 0, memCharCounter = 0;

    std::string buff;
    while (getline (inputFile, buff))
    {
        std::cout << buff << std::endl;
        for (size_t i = 0; i < buff.size (); i++)
        {
            auto c = buff[i];

            if (c == ' ')
                continue;

            charCounter++;

            switch (c)
            {
            case '"':
                continue;
            case '\\':
            {

                // Hexadecimal escape character
                if (buff[i + 1] == 'x')
                {
                    i += 3;
                    charCounter += 3;
                    memCharCounter++;
                }
                // Normal escap character
                else
                {
                    i++;
                    charCounter++;
                    memCharCounter++;
                }
                continue;
            }
            }

            memCharCounter++;
        }
    }

    std::cout << charCounter - memCharCounter << std::endl;

    return 0;
}
