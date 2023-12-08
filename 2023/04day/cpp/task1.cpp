/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 4 Advent of Code 2023
 *
 *        Version:  0.1.0
 *        Created:  04.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

std::vector<std::string> split(std::string source, char sep) {
    std::vector<std::string> res {};
    std::stringstream stream { source };
    for (std::string part; getline(stream, part, sep);) {
        res.push_back(part);
    }
    return res;
}

size_t get_card_id(std::string& part) {
    std::stringstream line { part };
    std::string card;
    size_t id {};
    line >> card >> id;
    (void)card;
    return id;
}

std::vector<int> get_numbers(std::string str) {
    std::stringstream sstream { str };
    std::vector<int> res {};
    int val;
    while (sstream >> val) {
        res.push_back(val);
    }
    return res;
}

size_t win_count (const std::vector<int>& cur, std::vector<int>& win) {
    size_t count = 0;
    for (const auto& n: cur) {
        auto pos = std::find(win.begin(), win.end(), n);
        if (pos != win.end()) {
            count++;
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    size_t count = 0;
    size_t overlap_count = 0;
    for (std::string line; getline(input, line);) {
        if (line.empty() || line == "\n") {
            // Skip empty line
            continue;
        }
        auto sep1 = split(line, ':');
        if (sep1.size() == 2) {
            size_t card_id = get_card_id(sep1[0]);
            auto sep2 = split(sep1[1], '|');
            if (sep2.size() == 2) {
                auto winning = get_numbers(sep2[0]);
                auto current = get_numbers(sep2[1]);
                size_t round_count = win_count(current, winning);
                std::cout << std::format("Parsed card {}: Win count {}\n", card_id, round_count);
                if (round_count > 1) {
                    count += (1<<(round_count - 1));
                } else {
                    count += round_count;
                }
                continue;
            }
        }
        std::cout << std::format("Failed to read line {} correctly.\n", line);

    }
    ::printf("Task 1: %zu\n", count);
    ::printf("Task 2: %zu\n", overlap_count);
    return 0;
}