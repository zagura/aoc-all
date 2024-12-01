/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2024 - Day 1
 *
 *        Version:  1.0
 *        Created:  1.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <map>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<int> left {};
    std::vector<int> right {};
    left.reserve(500);
    right.reserve(500);
    for (std::string line; std::getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss { line };
        int a, b;
        ss >> a >> b;
        left.push_back(a);
        right.push_back(b);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int distance = 0;
    uint64_t sum = 0;
    for (size_t i = 0; i < left.size(); i++) {
        if (left[i] < right[i]) {
            distance = right[i] - left[i];
        } else {
            distance = left[i] - right[i];
        }
        sum += distance;
        distance = 0;
    }
    ::printf("Task 1 result: %" PRIu64 "\n", sum);
    return 0;
}
