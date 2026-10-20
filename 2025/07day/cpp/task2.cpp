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

using Vec2 = std::vector<std::vector<uint64_t>>;


int pass_beam(size_t x, std::set<size_t>& ys, std::vector<std::string>& data, Vec2& passes) {
    int count = 0;
    std::set<size_t> new_ys {};
    for (const auto& y: ys) {
        uint64_t old_passes = passes[x-1][y];
        if (data[x][y] == '^') {
            new_ys.insert(y - 1);
            new_ys.insert(y + 1);
            count += 1;
            data[x][y-1] = '|';
            data[x][y+1] = '|';
            passes[x][y-1] += old_passes;
            passes[x][y+1] += old_passes;
        } else {
            data[x][y] = '|';
            passes[x][y] += old_passes;
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
    Vec2 passes = {};
    for (size_t i = 0; i < diagram.size(); i++) {
        std::vector<uint64_t> vec {};
        vec.resize(diagram.front().size());
        passes.push_back(vec);
    }
    size_t x = 0;
    size_t y = diagram.front().find('S');
    std::print("Starting from {}, {}\n", x, y);
    size_t total = 0;
    std::set<size_t> ys {};
    ys.insert(y);
    passes[0][y] = 1;
    for (x = 1; x < diagram.size(); x++) {
        total += pass_beam(x, ys, diagram, passes);
    }
    for (const auto& l: diagram) {
        std::print("{}\n", l);
    }
    uint64_t total_passes = 0;
    for (auto& p: passes.back()) {
        total_passes += p;
    }

    ::printf("Task 1 result: %" PRIu64 "\n", total);
    ::printf("Task 2 result: %" PRIu64 "\n", total_passes);
    return 0;
}
