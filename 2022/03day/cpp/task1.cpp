/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description: Day 3 Advent of Code 2022
 *
 *        Version:  0.1.0
 *        Created:  03.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;

size_t prio(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

char common(const std::string& l, const std::string& r) {
    for (const auto& c: r) {
        for (const auto& c2: l) {
            if  (c == c2) {
                return c;
            }
        }
    }
    return '\0';
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    size_t priority_sum = 0;
    for (std::string line; getline(input, line);) {
        std::string left, right;
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        left = line.substr(0, line.size() / 2);
        right = line.substr(line.size() / 2);
        ::printf("%zu: %zu and %zu\n", line.size(), left.size(), right.size());
//        ::printf("Line %s\n", line.c_str());
        std::sort(left.begin(), left.end());
        std::sort(right.begin(), right.end());
        char c = common(left, right);
        size_t priority = prio(c);
        priority_sum += priority;
        ::printf("%s|%s -> %c: %zu/%zu\n", left.c_str(), right.c_str(), c,
                                           priority, priority_sum);
    }

    ::printf("Part 1 result: %zu\n", priority_sum);
    return 0;
}
