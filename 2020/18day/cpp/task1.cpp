/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  13.12.2020
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
#include <vector>
#include <cinttypes>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

int64_t math_op(char op, int64_t left, int64_t right) {
    if (op == '+') {
        return left +  right;
    }
    return left * right;
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
    int64_t result = 0;
    int line_no = 0;
    for (string line; getline(input, line); line_no++) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::pair<int64_t, char>> partials {};
        std::stringstream line_stream { line };
        string token;
        char op = '+';
        int64_t current_result = 0;
        while (line_stream >> token) {
            printf("Token: %s\n", token.c_str());
            if (token.front() == '*' || token.front() == '+') {
                op = token.front();
            } else if (token.front() == '(') {

                size_t begin = 0;
                for (;token[begin] == '('; begin++) {
                    partials.emplace_back(current_result, op);
                    current_result = 0;
                    op = '+';
                }
                current_result = std::stoll(token.substr(begin));
            } else {
                size_t closing = token.find_first_of(')');
                current_result = math_op(op, current_result, std::stoll(token.substr(0, closing)));
                for (; closing < token.size(); closing++) {
                    auto [last_result, last_op] = partials.back();
                    partials.pop_back();
                    current_result = math_op(last_op, current_result, last_result);
                }
            }
        }
        printf("Line: %d - %" PRId64 "\n", line_no, current_result);
        result += current_result;
    }

    ::printf("Task 1 result: %" PRId64 "\n", result);
    return 0;
}

