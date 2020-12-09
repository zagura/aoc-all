/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

bool verify(const std::vector<int>& numbers, int number) {
    // size - 1 - element with number
    size_t last_index = numbers.size() - 2;
    for (int i = 0; i < 24; i++) {
        for (int j = i + 1; j < 25; j++) {
            if (numbers.at(last_index - i) + numbers.at(last_index - j) == number) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    int result = 0;
    int number {};
    std::vector<int> numbers {};
    std::vector<int> invalid {};
    invalid.reserve(100);
    numbers.reserve(1000);
    while (input >> number) {
        numbers.push_back(number);
        if (numbers.size() > 25) {
            bool valid = verify(numbers, number);
            if (not valid) {
                invalid.push_back(number);
            }
        }
    }

    ::printf("Task 1 result: %d\n", invalid[0]);
    return 0;
}

