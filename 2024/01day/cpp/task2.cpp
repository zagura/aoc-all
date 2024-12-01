/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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
    uint64_t total_score = 0;
    for (const auto& num: left) {
        size_t count = std::count_if(right.begin(), right.end(), [&num](int n) { return n == num; });
        total_score += (num * count);
    }
    ::printf("Task 2 result: %" PRIu64 "\n", total_score);
    return 0;
}
