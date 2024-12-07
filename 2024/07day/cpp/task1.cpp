/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  07.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <map>
#include <print>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
constexpr size_t task_size = 100000;

bool evaluate(const std::vector<int64_t>& numbers, size_t pos, const int64_t expected, const int64_t current_value) {
    if (pos == numbers.size()) {
        return current_value == expected;
    }
    return evaluate(numbers, pos + 1, expected, numbers[pos] * current_value)
           || evaluate(numbers, pos + 1, expected, numbers[pos] + current_value);
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
    std::vector<std::vector<int64_t>> numbers {};
    std::vector<int64_t> results {};
    for(std::string line; getline(input, line);) {
        if (line.size() == 0 || line == "\n") {
            continue;
        }
        std::stringstream s { line };
        uint64_t num;
        char c;
        s >> num >> c;
        results.push_back(num);
        std::vector<int64_t> line_numbers {};
        while(s >> num) {
            line_numbers.push_back(num);
        }
        numbers.push_back(line_numbers);
    }
    int64_t result = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        if (evaluate(numbers[i], 0, results[i], 0)) {
            result += results[i];
        }
    }
    std::println("Task 1 result: {}", result);

    return 0;
}

