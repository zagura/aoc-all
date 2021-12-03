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

std::vector<string> choose_by_bit(const std::vector<string>& numbers, size_t bit, bool common, bool one) {
    std::vector<string> chosen = {};
    for (auto n: numbers) {
        if ((common && one) || (!common && !one)) {
            if (n[bit] == '1') {
                chosen.push_back(n);
                printf("Add %s to bit_criteria (%zu, %d) by one\n", n.c_str(), bit, common);
            }
        } else if ((common && !one) || (!common && one)) {
            if (n[bit] == '0') {
                chosen.push_back(n);
                printf("Add %s to bit_criteria (%zu, %d) by zero\n", n.c_str(), bit, common);
            }
        }
    }
    return chosen;
}

std::string bit_criteria(const std::vector<string>& numbers, size_t bit, bool common) {
    std::vector<string> chosen {};
    std::size_t ones = 0;
    std::size_t zeros = 0;
    for (const auto& n: numbers) {
        if (n[bit] == '1') {
            ones++;
        } else if (n[bit] == '0') {
            zeros++;
        }
    }
    bool one = (ones > zeros);
    if (ones == zeros) {
        ::printf("Equal zeros and one count at bit (%zu) common %d\n", bit, common);
        one = true;
    }
    chosen = choose_by_bit(numbers, bit, common, one);
    std::string ret = chosen[0];
    if (chosen.size() > 1) {
        ret = bit_criteria(chosen, bit + 1, common);
    }
    return ret;
}

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
    string oxygen_generator = bit_criteria(numbers, 0, true);
    string co2_rating = bit_criteria(numbers, 0, false);

    size_t oxygen = 0;
    size_t co2 = 0;
    for (size_t mask = 0; mask < len; mask++) {
        size_t bit_value = (1 << (len - mask - 1));
        if (oxygen_generator[mask] == '1') {
            oxygen += bit_value;
        }
        if (co2_rating[mask] == '1') {
            co2 += bit_value;
        }
    }
    size_t life_support = oxygen * co2;

    ::printf("oxygen: %zu, co2 %zu, common %zu\n", oxygen, co2, life_support);
    ::printf("Task 2 result is: %zu\n", life_support);

    return 0;
}
