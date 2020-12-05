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
#include <algorithm>

int decode(std::string seat) {
    int position = 1 << (seat.length() - 1);
    int result = 0;
    for (char c: seat) {
        result += (c == 'B' || c == 'R') * position;
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
        fprintf(stderr, "Cannot open file.\n");
        return 2;
    }
    std::vector<int> numbers {};
    numbers.reserve(800);
    for (std::string line; getline(input, line);) {
        int number = decode(line);
        numbers.push_back(number);
    }
    std::sort(numbers.begin(), numbers.end());
    int last = numbers.front() - 1;
    for (int n: numbers) {
        if (n - last == 2) {
            printf("Task 2 (missing id: %d\n", n - 1);
        }
        last = n;
    }
    printf("Task 1 result: %d\n", numbers.back());
}
