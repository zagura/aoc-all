/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 6
 *
 *        Version:  1.0
 *        Created:  21.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <numeric>
#include <print>
#include <map>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::vector<uint64_t>> values {};
    std::vector<std::string> operators {};
    uint64_t total = 0;
    for (std::string line; getline(input, line);) {
        values.emplace_back();
        std::stringstream sline {line};
        uint64_t val {};
        while (sline >> val) {
            values.back().push_back(val);
        }
        if (values.back().size() == 0) {
            values.pop_back();
            // std::print("Last line: {}\n", line);
            sline = std::stringstream { line };
            std::string symbol = "";
            while(sline >> symbol) {
                std::vector<uint64_t> args {};
                for (const auto& row: values) {
                    args.push_back(row[operators.size()]);
                }
                uint64_t temp_result = 0;
                if (symbol == "*") {
                    temp_result = std::accumulate(args.begin(), args.end(), 1, std::multiplies<uint64_t>());
                } else if (symbol == "+") {
                    temp_result = std::accumulate(args.begin(), args.end(), 0, std::plus<uint64_t>());
                }
                std::print("Temp result from actions with '{}': {}\n", symbol, temp_result);
                total += temp_result;
                operators.emplace_back(symbol);
            }
        }
        std::print("Last row size: {}\n", values.back().size());
    }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
