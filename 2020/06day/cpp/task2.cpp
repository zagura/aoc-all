/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 6
 *
 *        Version:  0.1.0
 *        Created:  06.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::map<char, unsigned int> answer_count {};
    size_t total_count = 0;
    size_t responders = 0;
    for (std::string line; getline(input, line); ) {
        if (line.empty()) {
            total_count += std::count_if(answer_count.begin(), answer_count.end(),
                                         [responders](auto a) { return a.second == responders; });
            answer_count.clear();
            responders = 0;
        }
        else {
            responders++;
            for (auto c: line) {
                answer_count[c]++;
            }
        }
    }
    total_count += std::count_if(answer_count.begin(), answer_count.end(),
                                 [responders](auto a) { return a.second == responders; });
    ::printf("Task 2 result: %zu\n", total_count);
    return 0;
}

