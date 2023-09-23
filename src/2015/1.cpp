#include <iostream>
#include <string.h>

int main(int argc, char** argv) {
    char buf[10000];

    if (argc != 2) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    strcpy(buf, argv[1]);

    int length = strlen(buf);
    int result = 0;

    for (int i = 0; i < length; i++) {
        if (buf[i] == '(') result++;
        else result--;
    }

    std::cout << result << std::endl;

    return 0;
}