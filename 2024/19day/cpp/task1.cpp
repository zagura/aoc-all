/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024
 *
 *        Version:  0.1.0
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


int match_pattern(std::vector<std::string>& towels, std::string pattern) {
    int counter = 0;
    if (pattern.empty()) {
        throw std::runtime_error("Possible");
    }
    for (auto& t: towels) {
        if (pattern.starts_with(t)) {
            counter += match_pattern(towels, pattern.substr(t.size()));
        }
    }
    return counter;
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
    std::string line;
    std::getline(input, line);
    std::vector<std::string> towels = split(line, ',');
    size_t possible = 0;
    for (;std::getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        try {
        int test = match_pattern(towels, line);
        if (test > 0) {
            std::println("Pattern '{}' possible: {}", line, test);
            possible += 1;
        }
        } catch(std::runtime_error& e) {
            possible += 1;
        }
    }

    ::printf("Task 1 result: %zu\n", possible);
    return 0;
}

