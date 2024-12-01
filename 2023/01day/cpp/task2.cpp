/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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

std::array<std::string, 10> words {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

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
        std::vector<std::pair<int, int>> digits {};
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c >= '0' && c <= '9') {
                digits.emplace_back(i, c - '0');
            } else {
                for (size_t w = 0; w < words.size(); w++) {
                    std::string test = line.substr(i, words[w].size());
                    if (test.find(words[w]) != std::string::npos) {
                        digits.emplace_back(i, w);
                        break;
                    }
                }
            }
        }
        if (digits.size() < 2) {
//            std::cout << std::format("To short output in line: {}, found {} digits\n", line, digits.size());
        }
        values.push_back(digits.front().second * 10 + digits.back().second);
    }
    size_t total = 0;
    for (auto& n: values) {
        total += n;
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
