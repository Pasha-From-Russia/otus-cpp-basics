#include <ctime>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "highscore.h"

//----------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    const struct option longopts[] = {
        { "max",   required_argument, NULL, 'm' },
        { "level", required_argument, NULL, 'l' },
        { "table", no_argument,       NULL, 't' },
        { NULL,    0,                 NULL, 0   }
    };

    bool maxSet = false;
        int max = 100;
    int level;
    int ch;
    while ((ch = getopt_long(argc, argv, "m:l:t", longopts, NULL)) != -1) {
        switch (ch) {
        case 'm':
            if (maxSet) {
                std::cout << "Max value is already set" << std::endl;
                break;
            }
            max = atoi(optarg);
                        maxSet = true;
            break;
        case 't':
            hiscore("", -1);
            return EXIT_SUCCESS;
        case 'l':
            if (maxSet) {
                std::cout << "Max value is already set" << std::endl;
                break;
            }
            level = atoi(optarg);
            if (level < 1) {
                level = 1;
            } else if (level > 3) {
                level = 3;
            }
            if (level == 1) {
                max = 10;
            } else if (level == 2) {
                max = 50;
            } else {
                max = 100;
            }
            maxSet = true;
            break;
        default:
            break;
        }
    }

    std::string username;
    std::cout << "Enter your name: ";
    std::cin >> username;

    std::srand(std::time(nullptr));
    const int rnd = std::rand() % max + 1;
    int val = 0;
    int attempts = 0;

    std::cout << "The game starts! I generated a number from 1 to " << max << std::endl;

    while (true) {
        ++attempts;
        std::cout << "Enter value: ";
        std::cin >> val;
        if (val == rnd) {
            std::cout << "You won! Attempts = " << attempts << std::endl;
            hiscore(username, attempts);
            break;
        }
        if (val < rnd) {
            std::cout << "Bigger than " << val << std::endl;
            continue;
        }
        std::cout << "Less than " << val << std::endl;
    }
    return EXIT_SUCCESS;
}
