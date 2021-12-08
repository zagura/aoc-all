/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 8
 *
 *        Version:  0.1.0
 *        Created:  08.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

constexpr size_t out_len = 4;

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    size_t line_no = 0;
    size_t counter = 0;
    std::vector<std::pair<std::vector<std::string>, std::array<std::string, out_len>>> input_data;
    input_data.reserve(2000);
    for (std::string line; getline(input, line); line_no++) {
        std::stringstream line_stream { line };
        std::vector<std::string> left_side {};
        std::array<std::string, out_len> right_side {};
        bool outside = false;
        size_t outside_idx = 0;

        for (std::string token; getline(line_stream, token, ' '); ) {
            if (token == "|") {
                outside = true;
                continue;
            }
            if (outside) {
                right_side[outside_idx] = token;
                outside_idx++;
                if (token.size() < 5 || token.size() > 6) {
                    counter++;
                }
            } else {
                left_side.push_back(token);
            }
        }
        input_data.emplace_back(left_side, right_side);
    }


    ::printf("Task 1 result: %zu\n", counter);
    return 0;
}

