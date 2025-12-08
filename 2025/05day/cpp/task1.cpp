/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 5
 *
 *        Version:  1.0
 *        Created:  9.12.2025
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
#include <print>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::pair<long long int, long long int>> ranges {};
    std::vector<long long int> ids;
    bool ranges_done = false;
    for (std::string line; getline(input, line);) {
        if (line.empty()) {
            ranges_done = true;
            continue;
        }
        if (!ranges_done) {
            long long int left = std::stoll(line.substr(0, line.find('-')));
            long long int right = std::stoll(line.substr(line.find('-') + 1));
            ranges.emplace_back(left, right);
        } else {
            ids.push_back(std::stoll(line));
        }
    }
    for (auto [left, right]: ranges) {
        std::println("Range: {} to {}", left, right);
    }
    size_t total = 0;
    for (auto& n: ids) {
        for (auto& [l, r]: ranges) {
            if (l <= n and n <= r) {
                std::println("{} in [{}, {}]", n, l, r);
                total += 1;
                break;
            }
        }
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
