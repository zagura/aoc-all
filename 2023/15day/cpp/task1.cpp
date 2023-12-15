/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2023 - Day 15
 *
 *        Version:  0.1.0
 *        Created:  15.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <cstdio>
// #include <sstream>
// #include <algorithm>
// #include <array>
// #include <vector>
// #include <queue>
// #include <map>
// #include <set>

size_t hash_algo(const std::string& data) {
    size_t value = 0;
    for (const auto& c: data) {
        value += static_cast<unsigned int>(c + 0);
        value = value * 17;
        value = value % 0x100;
    }

    return value;
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
    size_t hash_sum = 0;
    for (std::string line; std::getline(input, line, ',');) {
        if (line.size() > 0) {
            if (line.back() == '\n') {
                line.pop_back();
            }
            size_t hash = hash_algo(line);
            hash_sum += hash;
            std::cout << std::format("Step {}: {}\n", line, hash);
        }
    }
    ::printf("Task 1 result: %zu\n", hash_sum);
    return 0;
}

