/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:i Day 3 Advent of Code 2020
 *
 *        Version:  0.1.0
 *        Created:  03.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> numbers {};
    for (std::string line; getline(input, line);) {
        if (line == "\n") {
            // Skip empty line
            continue;
        }
        numbers.push_back(line);
        ::printf("Line %s\n", line.c_str());
    }
    ::printf("numbers size %zu\n", numbers.size());
    size_t len = numbers[0].length();
    std::vector<int> one_counts(len);
    std::vector<int> zero_counts(len);
    for (auto& n: numbers) {
        size_t id = 0;
        for (auto& c: n) {
            if (c == '1') {
                one_counts[id] += 1;
            } else if (c == '0') {
                zero_counts[id] += 1;
            }
            id++;
        }
    }
    size_t gamma_rate = 0;
    size_t epsilon_rate = 0;
    for (size_t mask = 0; mask < len; mask++) {
        size_t curr_bit = (1 << (len - mask - 1));
        if (one_counts[mask] > zero_counts[mask]) {
            gamma_rate += curr_bit;
        } else {
            epsilon_rate += curr_bit;
        }
    }
    size_t power_consumption = gamma_rate * epsilon_rate;
    ::printf("Gamma: %zu, epsilon %zu, common %zu\n", gamma_rate, epsilon_rate,
                                                    power_consumption);
    ::printf("Task 1 result is: %zu\n", power_consumption);

    return 0;
}
