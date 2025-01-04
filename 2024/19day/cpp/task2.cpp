/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2024
 *
 *        Version:  0.1.1 - Add memoization
 *                  0.1.0 - Trival brute force recursive
 *        Created:  04.01.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <print>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

std::vector<std::string> split(std::string source, char sep) {
    std::vector<std::string> res {};
    std::stringstream stream { source };
    for (std::string part; getline(stream, part, sep);) {
        if (not part.empty()) {
            if (part[0] == ' ') {
                part = part.substr(1);
            }
            res.push_back(part);
        }
    }
    return res;
}

class PatternCheck {
public:
    std::map<std::string, uint64_t> mem;
    std::vector<std::string> towels;
    uint64_t match(const std::string &pattern) {
        uint64_t counter = 0;
        if (pattern.empty()) {
            return 1;
        }
        auto it = mem.find(pattern);
        if (it != mem.end()) {
            return it->second;
        }
        for (const auto &t : towels) {
            if (pattern.starts_with(t)) {
                counter += match(pattern.substr(t.size()));
            }
        }
        mem.emplace(pattern, counter);
        return counter;
    }
};
int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::string line;
    std::getline(input, line);
    std::vector<std::string> towels = split(line, ',');
    uint64_t possible = 0;
    uint64_t possible_sums = 0;
    for (;std::getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        PatternCheck check {};
        check.mem = {};
        check.towels = towels;
        uint64_t counter = check.match(line);
        if (counter > 0) {
            std::println("Pattern '{}' possible: {}", line, counter);
            possible += 1;
            possible_sums += counter;
        }

    }

    std::println("Task 1 result: {}", possible);
    std::println("Task 2 result: {}", possible_sums);
    return 0;
}

