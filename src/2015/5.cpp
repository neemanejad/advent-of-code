#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

enum LightOperation
{
    Toggle,
    TurnOn,
    TurnOff
};

struct Coord
{
    int x;
    int y;
};

struct LineInfo
{
    LightOperation type;
    Coord start;
    Coord end;
};

LineInfo getLineInfo (std::vector<std::string>);
Coord getCoords (std::string);

int
main (int argc, char **argv)
{
    if (argc < 2)
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

    bool lights[1000][1000];
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            lights[i][j] = false;
        }
    }

    auto updateLights = [&lights] (LineInfo info)
    {
        if (info.type == LightOperation::Toggle)
        {
            for (int i = info.start.x; i <= info.end.x; i++)
            {
                for (int j = info.start.y; j <= info.end.y; j++)
                {
                    lights[i][j] = !lights[i][j];
                }
            }
        }
        else
        {
            for (int i = info.start.x; i <= info.end.x; i++)
            {
                for (int j = info.start.y; j <= info.end.y; j++)
                {
                    lights[i][j]
                        = info.type == LightOperation::TurnOff ? false : true;
                }
            }
        }
    };

    std::string buff;
    while (getline (inFile, buff))
    {
        std::vector<std::string> lineParts;
        std::stringstream ss (buff);
        std::string word;
        while (ss >> word)
        {
            lineParts.push_back (word);
        }

        LineInfo info = getLineInfo (lineParts);
        updateLights (info);
    }

    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (lights[i][j])
                count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}

Coord
getCoords (std::string input)
{
    char *p = strtok ((char *)input.c_str (), ",");
    int x = atoi (p);
    p = strtok (NULL, ",");
    int y = atoi (p);
    return Coord ({ x, y });
}

LineInfo
getLineInfo (std::vector<std::string> lineParts)
{
    if (lineParts.size () != 4 && lineParts.size () != 5)
    {
        throw std::invalid_argument (
            "Didn't receive enough line parts to get line info");
    }

    LineInfo result;
    if (lineParts.size () == 4)
    {
        result.type = LightOperation::Toggle;

        result.start = getCoords (lineParts[1]);
        result.end = getCoords (lineParts[3]);
    }
    else
    {
        if (lineParts[0] == "turn" && lineParts[1] == "off")
        {
            result.type = LightOperation::TurnOff;
        }
        else
        {
            result.type = LightOperation::TurnOn;
        }

        result.start = getCoords (lineParts[2]);
        result.end = getCoords (lineParts[4]);
    }

    return result;
}
