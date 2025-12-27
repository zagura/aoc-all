/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 9
 *
 *        Version:  1.0
 *        Created:  28.12.2025
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
#include <map>

using Point = std::pair<uint64_t, uint64_t>;

uint64_t diff(uint64_t a, uint64_t b) {
    if (a < b) {
        return (b - a);
    }
    return (a - b);
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<Point> values {};
    for (std::string line; getline(input, line);) {
        uint64_t x = std::stoull(line.substr(0, line.find(',')));
        uint64_t y = std::stoull(line.substr(line.find(',') + 1));
        values.emplace_back(x, y);
    }
    uint64_t max_area = 0;
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            auto [x1, y1] = values[i];
            auto [x2, y2] = values[j];
            uint64_t area = (diff(x1, x2) + 1)* (diff(y1, y2) + 1);
            std::println("[{}, {}] -> [{}, {}]: {} x {} == {}", x1, y1, x2, y2, diff(x1, x2) + 1, diff(y1, y2) + 1, area);
            if (area > max_area) {
                max_area = area;
            }
        }
    }
    uint64_t total = max_area;
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
