/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 10
 *
 *        Version:  0.1.0
 *        Created:  10.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>

const std::map<char, int> scores {
    { ')', 3 },
    { ']', 57 },
    { '}', 1197 },
    { '>', 25137 }
};

const std::map<char, char> closes {
    { '(', ')' },
    { '[', ']' },
    { '{', '}' },
    { '<', '>' }
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
    size_t total_score = 0;
    int line_no = 0;
    for (std::string line; getline(input, line);) {
        line_no++;
        std::list<char> opens {};
        size_t pos = 0;
        for (auto& c: line) {
            if (closes.contains(c)) {
                opens.push_back(c);
            } else {
                if (c != closes.at(opens.back())) {
                    printf("  %s\n", line.c_str());
                    printf("syntax error: should be '%c' but found '%c' instead at line %d:%zu\n",
                           closes.at(opens.back()), c, line_no, pos);
                    total_score += scores.at(c);
                    break;
                }
                opens.pop_back();
            }
            pos++;
        }
    }


    ::printf("Task 1 result: %zu\n", total_score);
    return 0;
}

