/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01.12.2021 19:55
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cinttypes>
#include <fmt/format.h>
#include <map>

using std::string;


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    int x = 0, y = 0;
    for (std::string line; getline(input, line);) {
        if (line == "\n") {
            // Skip empty line
            continue;
        }
        std::stringstream stream { line };
        string direction;
        int value;
        stream >> direction >> value;
        if (direction == "forward") {
            x += value;
        } else if (direction == "down") {
            y -= value;
        } else if (direction == "up") {
            y += value;
        }
        printf("(%d, %d)\n", x, y);
    }
    uint64_t result = y * (-1) * x;
    ::printf("Task 1 result: %" PRIu64 "\n", result);
    return 0;
}
