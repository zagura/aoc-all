/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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
#include <vector>

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

const std::map<char, char> missing_scores {
    { ')', 1 },
    { ']', 2 },
    { '}', 3 },
    { '>', 4 }
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
    std::vector<size_t> autocomplete_scores {};
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
                    opens.clear();
                    break;
                }
                opens.pop_back();
            }
            pos++;
        }
        // incomplete lines
        if (opens.size() > 0) {
            size_t line_score = 0;
            for(auto it = opens.rbegin(); it != opens.rend(); it++) {
                line_score *= 5;
                printf("%c ", *it);
                line_score += missing_scores.at(closes.at(*it));
            }
            printf("%zu\n", line_score);
            autocomplete_scores.push_back(line_score);
        }
    }
    std::sort(autocomplete_scores.begin(), autocomplete_scores.end());
    size_t middle_score = autocomplete_scores.at(autocomplete_scores.size() / 2);
    ::printf("Task 2 result: %zu\n", middle_score);
    return 0;
}

