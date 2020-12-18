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

uint64_t math_op(char op, uint64_t left, uint64_t right, int l) {
    printf("%d: Calculate: %" PRId64 " %c %" PRId64 "\n", l, left, op, right);
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
    uint64_t result = 0;
    int line_no = 0;
    for (string line; getline(input, line); line_no++) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::pair<std::pair<uint64_t, uint64_t>, char>> partials {};
        uint64_t left_stack = 1;
        std::stringstream line_stream { line };
        string token;
        char op = '+';
        uint64_t current_result = 0;
        while (line_stream >> token) {
            printf("Token: %s\n", token.c_str());
            if (token.front() == '*' || token.front() == '+') {
                op = token.front();
            } else {
                ::printf("State: (%" PRId64 ", %" PRId64 ", %c)\n", left_stack, current_result, op);
                if (token.front() == '(') {
                    size_t begin = 0;
                    for (;token[begin] == '('; begin++) {
                            printf("Emplace: (%" PRId64 ", %" PRId64 ", %c)\n", left_stack, current_result, op);
                            partials.emplace_back(std::make_pair(left_stack, current_result), op);
                            current_result = 0;
                            left_stack = 1;
                            op = '+';
                    }
                    current_result = math_op(op, current_result, std::stoll(token.substr(begin)), __LINE__);
                } else {
                    size_t closing = token.find_first_of(')');
                    if (op == '*') {
                        left_stack = math_op(op, left_stack, current_result, __LINE__);
                        op = '+';
                        current_result = 0;
                    }
                    current_result = math_op(op, current_result, std::stoll(token.substr(0, closing)), __LINE__);
//                    ::printf("State3: (%" PRId64 ", %" PRId64 ", %c)\n", left_stack, current_result, op);
                    bool parens = (closing != std::string::npos);
                    if (parens) {
//                        partials.emplace_back(std::make_pair(left_stack, current_result), op);
                        uint64_t tmp_result = current_result * left_stack;
                        printf("Closing paren - evaluate to: %" PRId64 "\n", tmp_result);
                        for (++closing; closing < token.size(); closing++) {
                            printf("Closing paren\n");
                            auto [last_results, last_op] = partials.back();
                            ::printf("Pull partials: (%" PRId64 ", %" PRId64 ", %c)\n", last_results.first, last_results.second, last_op);
                            partials.pop_back();
                            tmp_result = math_op(last_op, tmp_result, last_results.second, __LINE__);
                            tmp_result = math_op('*', tmp_result, last_results.first, __LINE__);
                        }
                        current_result = tmp_result;
                        left_stack = 1;
                    }
                }
                ::printf("State end: (%" PRId64 ", %" PRId64 ", %c)\n", left_stack, current_result, op);
            }
        }

//        if (op == '*') {
        uint64_t tmp_result = math_op('*', left_stack, current_result, __LINE__);
        while (not partials.empty()) {
            auto [last_results, last_op] = partials.back();
            partials.pop_back();
            tmp_result = math_op(last_op, tmp_result, last_results.second, __LINE__);
            tmp_result = math_op('*', tmp_result, last_results.first, __LINE__);
        }
        current_result = tmp_result;

//        }

        printf("Line %d: %s - %" PRId64 "\n", line_no, line.c_str(), current_result);
        result += current_result;
    }

    ::printf("Task 2 result: %" PRId64 "\n", result);
    return 0;
}

