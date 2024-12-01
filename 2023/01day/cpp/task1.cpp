/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2023 - Day 1
 *
 *        Version:  1.0
 *        Created:  1.12.2023
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
    std::vector<int> values {};
    for (std::string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        std::vector<int> digits {};
        for (auto& c: line) {
            if (c >= '0' && c <= '9') {
                digits.push_back(c - '0');
            }
        }
        if (digits.size() < 2) {
//            std::cout << std::format("To short output in line: {}, found {} digits\n", line, digits.size());
        }
        values.push_back(digits.front() * 10 + digits.back());
    }
    size_t total = 0;
    for (auto& n: values) {
        total += n;
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
