/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 5
 *
 *        Version:  0.1.0
 *        Created:  05.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::string;

int decode(string seat) {
    int position = 1 << (seat.length() - 1);
    int result = 0;
    for (char c: seat) {
        int bit = 0;
        switch (c) {
        case 'B':
        case 'R':
            bit = 1;
            break;
        case 'L':
        case 'F':
            bit = 0;
            break;
        }
        result += bit * position;
        position >>= 1;
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        std::cerr << "Cannot open file" << std::endl;
        return 2;
    }
    int maximum = 0;
    for (string line; getline(input, line);) {
        int number = decode(line);
        if (number > maximum) {
            maximum = number;
        }
    }
    printf("Task 1 result: %d\n", maximum);

}
