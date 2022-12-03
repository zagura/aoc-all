/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description: Day 3 Advent of Code 2022
 *
 *        Version:  0.1.0
 *        Created:  03.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;
constexpr size_t group_size = 3;
size_t prio(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

char common(const std::string& l, const std::string& r) {
    for (const auto& c: r) {
        for (const auto& c2: l) {
            if  (c == c2) {
                return c;
            }
        }
    }
    return '\0';
}

char common(const std::array<std::string, group_size>& group) {
    printf("Common: %s, %s, %s\n", group[0].c_str(), group[1].c_str(), group[2].c_str());
    for (const auto c1: group[0]) {
        if (group[1].find(c1) != std::string::npos
            && group[2].find(c1) != std::string::npos) {
            return c1;
        }
        printf("%c: %zu, %zu\n", c1, group[1].find(c1), group[2].find(c1));
    }
    return '\0';

}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    size_t priority_sum = 0;
    size_t token_sum = 0;
    size_t line_no = 0;
    std::vector<std::array<std::string, group_size>> groups(100);
    for (std::string line; getline(input, line);) {
        std::string left, right;
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        left = line.substr(0, line.size() / 2);
        right = line.substr(line.size() / 2);
        ::printf("%zu: %zu and %zu\n", line.size(), left.size(), right.size());
        //        ::printf("Line %s\n", line.c_str());
        std::sort(left.begin(), left.end());
        std::sort(right.begin(), right.end());
        char c = common(left, right);
        size_t priority = prio(c);
        priority_sum += priority;
        ::printf("%s|%s -> %c: %zu/%zu\n", left.c_str(), right.c_str(), c,
                 priority, priority_sum);
        groups[line_no / 3][line_no % 3] = line;
        line_no++;
        if (line_no % 3 == 0) {
            char c2 = common(groups[line_no / 3 - 1]);
            size_t group_prio = prio(c2);
            token_sum += group_prio;
            ::printf("%c: %zu/%zu\n", c2, group_prio, token_sum);
        }
    }
    if (line_no / 3 < groups.size()) {
        groups.resize(line_no / 3);
    }

    ::printf("Part 1 result: %zu\n", priority_sum);
    ::printf("Part 2 result: %zu\n", token_sum);
    return 0;
}
