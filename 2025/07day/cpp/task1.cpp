/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 7
 *
 *        Version:  1.0
 *        Created:  24.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <print>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <map>
#include <set>


int pass_beam(size_t x, std::set<size_t>& ys, std::vector<std::string>& data) {
    int count = 0;
    std::set<size_t> new_ys {};
    for (const auto& y: ys) {
        if (data[x][y] == '^') {
            new_ys.insert(y - 1);
            new_ys.insert(y + 1);
            count += 1;
            data[x][y-1] = '|';
            data[x][y+1] = '|';
        } else {
            data[x][y] = '|';
            new_ys.insert(y);
        }
    }
    ys = new_ys;
    return count;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> diagram {};
    for (std::string line; getline(input, line);) {
        diagram.push_back(line);
    }
    // std::string horizontal = "";
    // for (const auto c: diagram.back()) {
    //     horizontal += ".";
    // }
    // diagram.push_back(horizontal);
    size_t x = 0;
    size_t y = diagram.front().find('S');
    std::print("Starting from {}, {}\n", x, y);
    size_t total = 0;
    std::set<size_t> ys {};
    ys.insert(y);
    for (x = 1; x < diagram.size(); x++) {
        total += pass_beam(x, ys, diagram);
    }
    for (const auto& l: diagram) {
        std::print("{}\n", l);
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
