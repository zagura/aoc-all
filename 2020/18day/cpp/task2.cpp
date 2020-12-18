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
#include <queue>
#include <variant>


using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using elem = std::variant<uint64_t, char>;

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

uint64_t math_op(char op, uint64_t left, uint64_t right, int l) {
    uint64_t result = 0;
    if (op == '+') {
        result = left + right;
    } else if (op == '*') {
        result = left * right;
    }
//    printf("%d: Calculate: %" PRIu64 " %c %" PRIu64 " => %" PRIu64 "\n", l,
//           left, op, right, result);
    return result;
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
        std::vector<elem> operators {};
        std::vector<elem> output {};
        std::stringstream line_stream { line };
        operators.reserve(line.size() / 2);
        output.reserve(line.size() / 2);
        string token;
        while (line_stream >> token) {
//            printf("Token: %s\n", token.c_str());
            if (token.front() == '*' || token.front() == '+') {
                char op = token.front();
                if (op == '*') {
                    while ((not operators.empty()) and
                           std::get<char>(operators.back()) == '+') {
                        output.emplace_back('+');
                        operators.pop_back();
                    }
                }
                operators.push_back(token.front());
            } else {
                if (token.front() == '(') {
                    size_t begin = 0;
                    for (;token[begin] == '('; begin++) {
                        operators.push_back(token[begin]);
                    }
                    uint64_t number = std::stoul(token.substr(begin));
                    output.emplace_back(number);
                } else {
                    size_t closing = token.find_first_of(')');
                    uint64_t number = std::stoul(token.substr(0, closing));
                    output.emplace_back(number);
                    for (; closing < token.size(); closing++) {
//                        printf("Closing paren\n");
                        while (std::get<char>(operators.back()) != '(') {
                            output.emplace_back(operators.back());
                            operators.pop_back();
                        }
                        operators.pop_back();
                    }
                }
            }
        }
        std::reverse(std::begin(operators), std::end(operators));
        for (auto& op: operators) {
            output.emplace_back(op);
        }
//        printf("Converted expression:");
//        for (auto& el: output) {
//            std::visit(overloaded {
//                           [](char c) { printf(" %c", c); },
//                           [](uint64_t n) { printf(" %" PRIu64 "", n); }
//                       }, el);
//        }
//        printf("\n");
        std::vector<uint64_t> stack {};
        stack.reserve(output.size());
        for (auto& el: output) {
            std::visit(overloaded {
                [&stack] (char c) { uint64_t res = math_op(c, stack.back(), stack.at(stack.size() - 2), __LINE__);
                                           stack.pop_back();
                                           stack.pop_back();
                                           stack.push_back(res);
                },
                [&stack] (uint64_t n) { stack.push_back(n); }
                       }, el);
        }
//        printf("Line %d: %" PRIu64 "\n", line_no, stack.front());
        result += stack.front();
        /// End of tokens in line
    }

    ::printf("Task 2 result: %" PRIu64 "\n", result);
    return 0;
}

