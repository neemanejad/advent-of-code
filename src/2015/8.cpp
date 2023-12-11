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

    /*
     * Part 2: Encode original string, get length,
     * and subtract encoded length from original length.
     */
    size_t encodedCharCounter = 0;
    charCounter = 0;
    inputFile.clear ();
    inputFile.seekg (inputFile.beg);
    while (getline (inputFile, buff))
    {
        for (size_t i = 0; i < buff.size (); i++)
        {
            charCounter++;
            encodedCharCounter++;
            auto c = buff[i];

            switch (c)
            {
            case '"':
            case '\\':
            {
                encodedCharCounter++;
            }
            }
        }

        // Add beginning and ending quotations for encoded string
        encodedCharCounter += 2;
    }

    std::cout << encodedCharCounter - charCounter << std::endl;

    return 0;
}
