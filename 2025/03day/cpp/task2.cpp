/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 1
 *
 *        Version:  1.0
 *        Created:  
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
    std::vector<std::string> values {};
    for (std::string line; getline(input, line);) {
        values.push_back(line);
    }
    size_t total = 0;
    for (auto& n: values) {
        total += n.size();
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
